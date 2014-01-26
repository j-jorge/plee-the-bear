/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::big_rabbit class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/forest/big_rabbit.hpp"

#include "ptb/defines.hpp"
#include "ptb/item/clingable.hpp"
#include "ptb/item/free_bonus.hpp"
#include "ptb/item/forest/carrot_monster.hpp"
#include "ptb/item/stone/stone.hpp"
#include "ptb/message/status_layer_boss_message.hpp"
#include "ptb/util/player_util.hpp"

#include "generic_items/camera_shaker.hpp"
#include "generic_items/decorative_effect.hpp"
#include "generic_items/decorative_item.hpp"
#include "generic_items/delayed_kill_item.hpp"
#include "generic_items/star.hpp"

#include "engine/export.hpp"
#include "engine/game.hpp"
#include "engine/world.hpp"

#include <claw/assert.hpp>
#include <boost/lexical_cast.hpp>

BASE_ITEM_EXPORT( big_rabbit, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::big_rabbit::big_rabbit()
: m_progress(NULL), m_elapsed_time(0), m_earth_effect_interval(0.03),
  m_jumping_from_underground(false), m_dead(false)
{
  set_z_fixed(false);
  set_mass(2000);
  set_density(1.5);
  set_friction(0.95);
  set_can_move_items(true);
  set_max_energy(1000);
  set_energy(1000);

  m_monster_type = monster::enemy_monster;
  set_offensive_phase(true);
  m_offensive_force = 10;
  m_offensive_coefficients[normal_attack] = 0;
  m_offensive_coefficients[indefensible_attack] = 1;

  m_clingable = new clingable();
} // big_rabbit::big_rabbit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::big_rabbit::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_model("model/forest/big_rabbit.cm");
  get_level_globals().load_model("model/forest/carrot_monster.cm");
  get_level_globals().load_animation("animation/effect/clod.canim");
} // big_rabbit::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::big_rabbit::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor
    ( get_level_globals().get_model("model/forest/big_rabbit.cm") );

  new_item(*m_clingable);
} // big_rabbit::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( !m_dead && (get_energy() == 0) && has_bottom_contact() )
    start_model_action("die");
  else
    {
      if ( m_progress != NULL )
        (this->*m_progress)(elapsed_time);

      adjust_clingable();

      m_elapsed_time += elapsed_time;
    }
} // big_rabbit::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c list of item.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::big_rabbit::set_item_list_field
( const std::string& name, const std::vector<bear::engine::base_item*>& value)
{
  bool ok = true;

  if (name == "big_rabbit.carrot_position")
    for( std::size_t i=0; i!=value.size(); ++i )
      m_carrot_positions.push_back( handle_type(value[i]) );
  else
    ok = super::set_item_list_field(name, value);

  return ok;
} // big_rabbit::set_item_list_field()

/*----------------------------------------------------------------------------*/
/**
 * Tell if the rabbit is in his second attack phase.
 */
bool ptb::big_rabbit::in_second_attack_phase() const
{
  return get_energy() <= get_max_energy() / 2;
} // big_rabbit::in_second_attack_phase()

/*----------------------------------------------------------------------------*/
/**
 * Return the prefered position where this item can be attacked.
 */
bear::universe::position_type ptb::big_rabbit::get_attack_point() const
{
  bear::engine::model_mark_placement m;

  if ( get_mark_placement("snout", m) )
    return m.get_position();
  else
    return this->get_center_of_mass();
} // monster_item::get_attack_point()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::big_rabbit::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( dynamic_cast<carrot_monster*>(&that) != NULL )
    return;

  if ( info.get_collision_side() != bear::universe::zone::bottom_zone )
    if ( default_collision(info) )
      ;

  if ( collision_and_attack(that, info) )
    ;
} // big_rabbit::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the items concerned by a progress/move of this one.
 * \param d (out) A list to which are added such items.
 */
void ptb::big_rabbit::get_dependent_items
( bear::universe::physical_item::item_list& d ) const
{
  super::get_dependent_items(d);
  d.push_back(m_clingable);
} // big_rabbit::get_dependent_items()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the big rabbit that he has no enery anymore.
 * \param attacker The monster that killed the rabbit.
 */
void ptb::big_rabbit::inform_no_energy(const monster& attacker)
{
  // prevent the item for being killed by not calling super::inform_no_energy()
} // big_rabbit::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get filename of bonus picture.
 */
std::string ptb::big_rabbit::get_bonus_picture_filename() const
{
  return "gfx/forest/bonus-icons/bonus-icons.png";
} // big_rabbit::get_bonus_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get name of bonus picture.
 */
std::string ptb::big_rabbit::get_bonus_picture_name() const
{
  return "boss";
} // big_rabbit::get_bonus_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state idle.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress_idle( bear::universe::time_type elapsed_time )
{
  player_proxy p1 = util::find_player( get_level_globals(), 1 );
  bool mirror = get_rendering_attributes().is_mirrored();

  if( p1 != NULL )
    mirror = p1.get_right() < get_left();

  get_rendering_attributes().mirror(mirror);
} // big_rabbit::progress_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state jump.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress_jump( bear::universe::time_type elapsed_time )
{
  if( get_speed().y < 0 )
    {
      m_jumping_from_underground = false;
      start_model_action("fall");
    }
  else if ( m_jumping_from_underground )
    {
      bear::engine::base_item* item =
        create_piece_of_ground
        ( get_horizontal_middle(), get_bottom(), get_width() / 2, 0 );
      item->set_z_position( get_z_position() + 10 );
    }
} // big_rabbit::progress_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state fall.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress_fall( bear::universe::time_type elapsed_time )
{
  if ( has_bottom_contact() )
    {
      start_model_action("idle");

      bear::camera_shaker::shake_around
        ( *this, 80, 1,
          get_level_globals().new_sample("sound/effect/earthquake.ogg") );

      player_proxy p1 = util::find_player( get_level_globals(), 1 );
      player_proxy p2 = util::find_player( get_level_globals(), 2 );
      bool mirror = get_rendering_attributes().is_mirrored();

      if( p1 != NULL )
        {
          if ( p1.has_bottom_contact() )
            p1.apply_paralyze(2.5);

          mirror = p1.get_right() < get_left();
        }

      if( p2 != NULL )
        if ( p2.has_bottom_contact() )
          p2.apply_paralyze(2.5);

      get_rendering_attributes().mirror(mirror);
    }
  else if( get_speed().y > 0 )
    start_model_action("jump");
} // big_rabbit::progress_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the carrot creation state.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress_create_carrot
( bear::universe::time_type elapsed_time )
{
  if ( m_elapsed_time >= get_current_action()->get_duration() )
    jump_on_player();
  else if ( (unsigned int)((m_elapsed_time + elapsed_time) / m_progress_step)
            > (unsigned int)(m_elapsed_time / m_progress_step) )
    create_straight_carrot();
} // big_rabbit::progress_create_carrot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the carrot creation state.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress_create_carrot_radial
( bear::universe::time_type elapsed_time )
{
  if ( m_elapsed_time >= get_current_action()->get_duration() )
    start_model_action("dig");
  else if ( (unsigned int)((m_elapsed_time + elapsed_time) / m_progress_step)
            > (unsigned int)(m_elapsed_time / m_progress_step) )
    create_radial_carrot();
} // big_rabbit::progress_create_carrot_radial()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the self attack.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress_self_attack
( bear::universe::time_type elapsed_time )
{
  if ( m_elapsed_time >= get_current_action()->get_duration() )
    jump_on_player();
  else if ( (unsigned int)((m_elapsed_time + elapsed_time) / m_progress_step)
            > (unsigned int)(m_elapsed_time / m_progress_step) )
    create_snout_carrot();
} // big_rabbit::progress_self_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the digging state.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress_dig( bear::universe::time_type elapsed_time )
{
  bear::engine::model_mark_placement m;

  if ( !get_mark_placement( "blast", m ) )
    return;

  bear::engine::base_item* item =
    create_piece_of_ground( m.get_position().x, m.get_position().y, 100, 0 );

  const double fx = 10000;
  const double fy = 100000;

  item->add_external_force
    ( bear::universe::force_type
      ( -fx + 2 * fx * (double)rand() / RAND_MAX,
        fy + fy * (double)rand() / RAND_MAX ) );
} // big_rabbit::progress_dig()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the underground state.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::big_rabbit::progress_underground
( bear::universe::time_type elapsed_time )
{
  m_earth_level =
    std::min
    ( m_earth_level + m_earth_level_increment * elapsed_time, get_height() );

  if ( (long)((m_elapsed_time + elapsed_time) / m_earth_effect_interval)
       > (long)(m_elapsed_time / m_earth_effect_interval) )
    generate_underground_earth();

  // Move the rabbit toward a player.
  player_proxy p = util::find_player(get_level_globals(), 2);

  if ( (p == NULL) || (rand() < RAND_MAX / 2) )
    p = util::find_player(get_level_globals(), 1);

  bear::universe::force_type f(5e6, 0);

  if ( p.get_center_of_mass().x < get_center_of_mass().x )
    f.x = -f.x;

  add_internal_force(f);
} // big_rabbit::progress_underground()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start idle state.
 */
void ptb::big_rabbit::start_idle()
{
  set_progress( &big_rabbit::progress_idle );
} // big_rabbit::start_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start dying.
 */
void ptb::big_rabbit::start_die()
{
  m_dead = true;
  set_offensive_phase(false);
  set_progress( NULL );
} // big_rabbit::start_die()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to be dead.
 */
void ptb::big_rabbit::start_dead()
{
  set_progress(NULL);

  create_floating_score("body", "head");
  inform_dead();
} // big_rabbit::start_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to fall.
 */
void ptb::big_rabbit::start_fall()
{
  set_progress( &big_rabbit::progress_fall );
} // big_rabbit::start_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to jump.
 */
void ptb::big_rabbit::start_jump()
{
  set_progress( &big_rabbit::progress_jump );
} // big_rabbit::start_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to create carrot.
 */
void ptb::big_rabbit::start_create_carrot()
{
  m_carrot_number = 0;
  m_carrot_index_delta = 5 * (double)rand() / RAND_MAX;

  m_progress_step =
    get_action( get_current_action_name() )->get_duration()
    / (double)m_carrot_positions.size();

  if ( in_second_attack_phase() )
    set_progress( &big_rabbit::progress_create_carrot_radial );
  else
    set_progress( &big_rabbit::progress_create_carrot );
} // big_rabbit::start_create_carrot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to send an attack of the snout.
 */
void ptb::big_rabbit::start_self_attack()
{
  m_carrot_number = 0;
  m_progress_step = 1 / (double)m_carrot_positions.size();

  set_progress( &big_rabbit::progress_self_attack );
} // big_rabbit::start_self_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to dig.
 */
void ptb::big_rabbit::start_dig()
{
  set_progress( &big_rabbit::progress_dig );
} // big_rabbit::start_dig()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to evolve underground.
 */
void ptb::big_rabbit::start_underground()
{
  m_earth_level = 0;
  m_earth_level_increment = 20;
  set_progress( &big_rabbit::progress_underground );
} // big_rabbit::start_underground()

/*----------------------------------------------------------------------------*/
/**
 * \brief Prepare to stop evolving underground.
 */
void ptb::big_rabbit::finish_underground()
{
  m_earth_level_increment = -20;
} // big_rabbit::finish_underground()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to jump out of the ground.
 */
void ptb::big_rabbit::start_jump_from_ground()
{
  create_ground_blast();

  m_jumping_from_underground = true;
  jump_on_player();
} // big_rabbit::start_jump_from_ground()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the current progress function.
 * \param f The function.
 */
void ptb::big_rabbit::set_progress( progress_function_type f )
{
  m_progress = f;
  m_elapsed_time = 0;
} // big_rabbit::set_progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the ground blast decoration.
 */
void ptb::big_rabbit::create_ground_blast() const
{
  bear::visual::animation blast
    ( get_level_globals().get_animation
      ("animation/effect/ground-blast.canim") );
  bear::visual::animation blast_side
    ( get_level_globals().get_animation
      ("animation/effect/ground-blast-side.canim") );

  bear::delayed_kill_item* killer = new bear::delayed_kill_item();
  killer->set_duration(0.5);
  new_item(*killer);

  blast.set_intensity( 0.69, 0.47, 0.07 );
  blast_side.set_intensity( 0.69, 0.47, 0.07 );

  bear::decorative_item* item = new bear::decorative_item();
  item->set_animation(blast);
  new_item(*item);
  item->set_left( get_center_of_mass().x - blast.width() / 2 );
  item->set_bottom( get_bottom() );
  killer->add_item(item);

  item = new bear::decorative_item();
  item->set_animation(blast_side);
  new_item(*item);
  item->set_left( get_center_of_mass().x + blast.width() / 2 );
  item->set_bottom( get_bottom() );
  killer->add_item(item);

  blast_side.mirror(true);
  item = new bear::decorative_item();
  item->set_animation(blast_side);
  new_item(*item);
  item->set_right( get_center_of_mass().x - blast.width() / 2 );
  item->set_bottom( get_bottom() );
  killer->add_item(item);
} // big_rabbit::create_ground_blast()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a carrot.
 */
bear::engine::base_item* ptb::big_rabbit::create_carrot() const
{
  return create_carrot(m_carrot_number);
} // big_rabbit::create_carrot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a carrot.
 * \param i The index of the position at which the carrot is created.
 */
bear::engine::base_item* ptb::big_rabbit::create_carrot( std::size_t i ) const
{
  CLAW_PRECOND( i < m_carrot_positions.size() );

  carrot_monster* new_carrot = new carrot_monster;
  const bear::universe::position_type pos
    ( m_carrot_positions[i]->get_center_of_mass() );

  new_item( *new_carrot );

  new_carrot->set_center_of_mass(pos);
  new_carrot->set_z_position( get_z_position() - 10000 );

  return new_carrot;
} // big_rabbit::create_carrot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a carrot that goes straight upward.
 */
void ptb::big_rabbit::create_straight_carrot()
{
  if ( m_carrot_number == m_carrot_positions.size() )
    return;

  const bear::universe::position_type pos
    ( m_carrot_positions[m_carrot_number]->get_center_of_mass() );

  if ( (rand() / (double)RAND_MAX < 1.0 / 2.0)
       && ( (pos.x < get_left()) || (pos.x > get_right()) ) )
    {
      bear::engine::base_item* new_carrot = create_carrot();
      new_carrot->set_system_angle( 3.14159 / 2 );
    }

  ++m_carrot_number;
} // big_rabbit::create_straight_carrot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create some carrots that go in a radial way.
 */
void ptb::big_rabbit::create_radial_carrot()
{
  const std::size_t count(5);
  const std::size_t interval(7);

  const std::size_t index =
    std::size_t(m_carrot_number / interval) * interval + m_carrot_index_delta;

  if ( index >= m_carrot_positions.size() )
    return;

  if ( (m_carrot_number - m_carrot_index_delta) % interval < count )
    {
      bear::engine::base_item* new_carrot = create_carrot(index);
      new_carrot->set_system_angle
        ( ((m_carrot_number - m_carrot_index_delta) % interval + 1) * 3.14159
          / (count + 1) );
    }

  ++m_carrot_number;
} // big_rabbit::create_radial_carrot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a carrot that goes toward the snout.
 */
void ptb::big_rabbit::create_snout_carrot()
{
  if ( m_carrot_number == m_carrot_positions.size() )
    return;

  if ( m_carrot_number <= m_carrot_positions.size() / 2 )
    {
      const std::size_t i = m_carrot_number + m_carrot_positions.size() / 4;
      bear::engine::base_item* new_carrot = create_carrot(i);

      const bear::universe::position_type pos
        ( new_carrot->get_center_of_mass()
          + bear::universe::position_type( 0, 5 ) );
      new_carrot->set_center_of_mass( pos );

      const bear::universe::position_type ref
        ( m_clingable->get_center_of_mass() );

      new_carrot->set_system_angle( std::atan2(ref.y - pos.y, ref.x - pos.x) );
    }

  ++m_carrot_number;
} // big_rabbit::create_snout_carrot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Jump on a player.
 */
void ptb::big_rabbit::jump_on_player()
{
  player_proxy p = util::find_player( get_level_globals(), 2 );

  if ( (p == NULL) || (rand() < RAND_MAX / 2) )
    p = util::find_player( get_level_globals(), 1 );

  jump_to( p.get_horizontal_middle() );
} // big_rabbit::jump_on_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Fill the map used to get the initial speed for the jumps.
 * \param d The maximum duration of the jumps.
 */
void ptb::big_rabbit::fill_jump_map( bear::universe::time_type d )
{
  const bear::universe::time_type time_step
    ( bear::engine::game::get_instance().get_time_step() / 1000.0 );
  std::size_t count=0;

  for( bear::universe::time_type t=0.0; t<=d; t+=time_step, ++count )
    {
      const bear::universe::time_type tc( t / time_step );
      const double b( std::pow(get_friction(), tc) );
      const bear::universe::coordinate_type speed =
        get_owner().get_speed_epsilon().x / b;

      bear::universe::coordinate_type dist = 0;
      bear::universe::coordinate_type s(speed);

      for ( std::size_t i=0; i!=count; ++i )
        {
          s *= get_friction();
          dist += s * time_step;
        }

      m_jump_map[dist] = speed;
    }
} // big_rabbit::fill_jump_map()

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the speed to apply on the x axis to jump on a given distance.
 * \param d The distance.
 */
double ptb::big_rabbit::get_jump_speed( bear::universe::coordinate_type d )
{
  if ( d < 0 )
    return -get_jump_speed(-d);

  if ( m_jump_map.empty() )
    fill_jump_map(3);

  const jump_map_type::const_iterator it = m_jump_map.upper_bound(d);

  if ( it == m_jump_map.begin() )
    return it->second;

  jump_map_type::const_iterator prev(it);
  --prev;

  if ( it == m_jump_map.end() )
    {
      claw::logger << claw::log_warning << "The rabbit can't jump so far ("
                   << d << "). Max distance is " << prev->first << std::endl;
      return prev->second;
    }

  if ( (d - prev->second) < (d - it->second) )
    return prev->second;

  return it->second;
} // get_jump_speed()

/*---------------------------------------------------------------------------*/
/**
 * \brief Jump to a given x position.
 * \param x The x position.
 */
void ptb::big_rabbit::jump_to( bear::universe::coordinate_type x )
{
  bear::camera_shaker::shake_around( *this, 40, 0.2 );

  x = std::min
    ( std::max
      (x, m_carrot_positions.front()->get_horizontal_middle()),
      m_carrot_positions.back()->get_horizontal_middle() );

  set_speed
    ( bear::universe::speed_type
      ( get_jump_speed( x - get_center_of_mass().x ), 2700 ) );

  start_model_action("jump");
} // big_rabbit::jump_to()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if the big_rabbit is in the sky and change state thereof.
 *         Return true if the big_rabbit is in the sky.
 */
bool ptb::big_rabbit::test_in_sky()
{
  bool result = false;

  if ( !has_bottom_contact() )
    {
      result = true;

      if( get_speed().y <= 0 )
        start_model_action("fall");
      else
        start_model_action("jump");
    }

  return result;
} // big_rabbit::test_in_sky()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the position and the size of the clingable.
 */
void ptb::big_rabbit::adjust_clingable() const
{
  const bear::engine::base_item* mark = get_model_mark_item("snout");

  if ( mark == NULL )
    {
      if ( m_clingable->has_owner() )
        m_clingable->get_layer().drop_item(*m_clingable);
    }
  else
    {
      bear::universe::position_type pos( mark->get_center_of_mass() );

      if ( get_rendering_attributes().is_mirrored() )
        pos.x -= 3;
      else
        pos.x += 3;

      m_clingable->set_size( mark->get_width(), 5 );
      m_clingable->set_center_of_mass( pos );

      if ( !m_clingable->has_owner() )
        get_layer().add_item(*m_clingable);
    }
} // big_rabbit::adjust_clingable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration representing a piece of earth.
 * \param x The x-coordinate of the center of mass of the decoration.
 * \param y The y-coordinate of the center of mass of the decoration.
 * \param dx A maximum random shift applied to x.
 * \param dy A maximum random shift applied to y.
 */
bear::engine::base_item* ptb::big_rabbit::create_piece_of_ground
( bear::universe::coordinate_type x, bear::universe::coordinate_type y,
  bear::universe::coordinate_type dx, bear::universe::coordinate_type dy ) const
{
  const bool create_stone = (double)rand() / RAND_MAX < 0.01;
  bear::engine::base_item* const item =
    create_stone ? create_stone_bonus() : create_earth_decoration();

  initialize_ground_object(item, x, y, dx, dy);

  bear::decorative_effect* e = new bear::decorative_effect();
  const double f = (double)rand() / RAND_MAX;

  e->set_item(item, true);
  e->set_global(true);

  if ( create_stone )
    e->set_duration(4);
  else
    {
      e->set_angle_offset( rand(), rand() );
      e->set_size_factor( 0.5 + f / 2, 0.5 + f / 2 ); // constant factor
      e->set_duration(2);
    }

  new_item(*e);

  return item;
} // big_rabbit::create_piece_of_ground()

/*----------------------------------------------------------------------------*/
/**
 * \brief Place an item representing a piece of the ground.
 * \param item The item to initialize.
 * \param x The x-coordinate of the center of mass of the decoration.
 * \param y The y-coordinate of the center of mass of the decoration.
 * \param dx A maximum random shift applied to x.
 * \param dy A maximum random shift applied to y.
 */
void ptb::big_rabbit::initialize_ground_object
( bear::engine::base_item* item, bear::universe::coordinate_type x,
  bear::universe::coordinate_type y, bear::universe::coordinate_type dx,
  bear::universe::coordinate_type dy ) const
{
  item->set_mass(1);
  item->set_z_position( get_z_position() - 1 );

  item->set_center_of_mass
    ( x - dx + 2 * dx * (double)rand() / RAND_MAX,
      y - dy + 2 * dy * (double)rand() / RAND_MAX );
} // big_rabbit::initialize_ground_object()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a stone bonus.
 */
bear::engine::base_item* ptb::big_rabbit::create_stone_bonus() const
{
  free_bonus* const item = new free_bonus();

  item->set_type( free_bonus::stones_stock );
  new_item(*item);

  return item;
} // big_rabbit::create_stone_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration representing a piece of earth.
 */
bear::engine::base_item* ptb::big_rabbit::create_earth_decoration() const
{
  bear::decorative_item* const item = new bear::decorative_item();
  item->set_animation
    ( get_level_globals().get_animation("animation/effect/clod.canim") );
  item->set_kill_on_contact(true);
  item->set_kill_when_leaving(true);

  const double intensity = 0.7 + 0.3 * (double)rand() / RAND_MAX;
  item->get_rendering_attributes().set_intensity
    (0.69 * intensity, 0.47 * intensity, 0.07 * intensity);

  new_item(*item);

  return item;
} // big_rabbit::create_earth_decoration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Generate the heap of earth when the rabbit is underground.
 */
void ptb::big_rabbit::generate_underground_earth() const
{
  bear::universe::coordinate_type x=20 * (double)rand() / RAND_MAX;
  bear::delayed_kill_item* earth_killer = new bear::delayed_kill_item();
  earth_killer->set_duration(0.25);
  earth_killer->set_global(true);

  bear::delayed_kill_item* stone_killer = new bear::delayed_kill_item();
  stone_killer->set_duration(4);
  stone_killer->set_global(true);

  while ( x < get_width() )
    {
      const bear::universe::coordinate_type y =
        std::sin( std::acos( x / (get_width() / 2) - 1 ) ) * get_height()
        + 20 * (double)rand() / RAND_MAX;

      const bool create_stone = (double)rand() / RAND_MAX < 0.01;
      bear::engine::base_item* const item =
        create_stone ? create_stone_bonus() : create_earth_decoration();

      initialize_ground_object(item, get_left() + x, get_bottom() + y, 5, 5);

      if ( create_stone )
        stone_killer->add_item(item);
      else
        earth_killer->add_item(item);

      x += 20 + 10 * (double)rand() / RAND_MAX;
    }

  new_item(*earth_killer);
  new_item(*stone_killer);
} // big_rabbit::generate_underground_earth()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item on the head of the rabbit.
 * \param mark The item representing the mark.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::big_rabbit::on_head_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  if ( m_dead )
    mark.default_collision(info);
  else if ( collision_and_attack(that, info) )
    ;

  monster* other = dynamic_cast<monster*>(&that);

  if (other != NULL)
    other->attack(*this);
} // big_rabbit::on_head_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item on the snout.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::big_rabbit::on_snout_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  if ( ( info.get_collision_side() == bear::universe::zone::middle_zone )
       || m_dead )
    return;

  mark.default_collision(info);

  player_proxy p(&that);

  if ( (p != NULL) && p.is_in_offensive_phase() )
    start_model_action("self_attack");
  else
    {
      monster* other = dynamic_cast<monster*>(&that);

      if ( other != NULL )
        {
          other->attack(*this);
          start_model_action("self_attack");
        }
      else
        attack(that);
    }
} // big_rabbit::on_snout_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process an attack on the snout.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::big_rabbit::on_snout_attacked
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  carrot_monster* m = dynamic_cast<carrot_monster*>(&that);

  if ( m != NULL )
    {
      if ( m->is_in_offensive_phase() )
        {
          // the carrots always injure the rabbit
          if ( get_energy() < 5 )
            set_energy( 0 );
          else
            set_energy( get_energy() - 5 );

          m->set_z_position( mark.get_z_position() );
          m->create_hit_star(mark);
          mark.default_collision(info);
          injure(*m, bear::universe::zone::middle_zone,
                 monster::s_injured_duration);
        }
    }
  else
    {
      const bear::universe::zone::position s = info.get_collision_side();

      if ( ( (s == bear::universe::zone::middle_right_zone)
             && !get_rendering_attributes().is_mirrored() )
        || ( (s == bear::universe::zone::middle_left_zone)
             && get_rendering_attributes().is_mirrored() ) )
        mark.default_collision(info);
    }
} // big_rabbit::on_snout_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item on the tooth.
 * \param mark The item associated with the mark of the tooth.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::big_rabbit::on_tooth_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{

} // big_rabbit::on_tooth_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::big_rabbit::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_die, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_dead, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_idle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_fall, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_create_carrot, void);
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_self_attack, void);
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_dig, void);
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_underground, void);
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, finish_underground, void);
  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, start_jump_from_ground, void);

  TEXT_INTERFACE_CONNECT_METHOD_0( big_rabbit, jump_on_player, void);

  TEXT_INTERFACE_CONNECT_METHOD_1
    ( big_rabbit, jump_to, void, bear::universe::coordinate_type );

  TEXT_INTERFACE_CONNECT_METHOD_3
    ( big_rabbit, on_head_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( big_rabbit, on_snout_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( big_rabbit, on_snout_attacked, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( big_rabbit, on_tooth_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
} // big_rabbit::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::big_rabbit )
