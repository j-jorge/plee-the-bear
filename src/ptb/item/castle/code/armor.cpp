/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::armor class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/armor.hpp"
#include "ptb/item/castle/axe.hpp"
#include "ptb/item/stone/stone.hpp"
#include "ptb/util/player_util.hpp"

#include "engine/world.hpp"
#include "engine/export.hpp"

#include "generic_items/decorative_item.hpp"

#include <claw/assert.hpp>

BASE_ITEM_EXPORT( armor, ptb )

const unsigned int ptb::armor::s_soul_energy = 40;
const unsigned int ptb::armor::s_scan_axe_distance = 350;
const unsigned int ptb::armor::s_scan_wait_distance = 200;
const unsigned int ptb::armor::s_scan_punch_distance = 100;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::armor::armor()
  : m_progress(NULL), m_max_distance(200),
    m_walk_force(bear::universe::force_type(40000, 0)),
    m_has_axe(true), m_has_head(true)
{
  set_z_fixed(false);
  set_mass(100);
  set_density(2);

  m_monster_type = monster::enemy_monster;
  m_energy = 30;
  m_offensive_phase = true;
  m_offensive_force = 10;
  m_offensive_coefficients[normal_attack] = 1;
  m_defensive_powers[air_attack] = true;
  m_defensive_powers[fire_attack] = true;
  m_defensive_powers[water_attack] = true;
  get_rendering_attributes().mirror(false);
  set_category("armor");
} // armor::armor()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::armor::~armor()
{
} // armor::~armor()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::armor::pre_cache()
{
  get_level_globals().load_image("gfx/castle/armor/armor-parts.png");
  get_level_globals().load_animation
    ("animation/forest/gorilla/gorilla_soul.canim");
  get_level_globals().load_model("model/castle/armor.cm");
  get_level_globals().load_model("model/headstone.cm");
  get_level_globals().load_model("model/castle/axe.cm");
} // armor::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::armor::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/castle/armor.cm") );
  // TODO
  // set_counter_picture("gfx/wastle/bonus-icons/bonus-icons.png","armor");
  start_model_action("idle");
  m_progress = &armor::progress_idle;
  m_origin_position = get_center_of_mass();
} // armor::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::armor::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // armor::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
*/
void ptb::armor::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  super::collision(that, info);

  if ( get_current_action_name() == "idle" )
    {
      stone* other = dynamic_cast<stone*>(&that);

      if ( other != NULL )
        {
          start_model_action("wake_up");

          if ( ( info.get_collision_side() ==
                 bear::universe::zone::middle_left_zone ) ||
               ( info.get_collision_side() ==
                 bear::universe::zone::middle_left_zone ) ||
               ( info.get_collision_side() ==
                 bear::universe::zone::middle_left_zone ) )
            get_rendering_attributes().mirror(true);
          else
            get_rendering_attributes().mirror(false);
        }
    }
}// armor::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::armor::set_real_field
( const std::string& name, double value )
{
  bool ok = true;

  if (name == "armor.max_distance")
    m_max_distance = value;
  else
    ok = super::set_real_field(name, value);

  return ok;
} // armor::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::armor::inform_no_energy(const monster& attacker)
{
  m_is_injured = false;

  if ( get_current_action_name() != "dead" )
    {
      set_speed( bear::universe::speed_type(0, 0) );
      set_acceleration( bear::universe::force_type(0, 0) );
      set_internal_force(bear::universe::force_type(0, 0));
      set_external_force(bear::universe::force_type(0, 0));
      start_dead();
      die(attacker);
    }
} // armor::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::armor::leaves_active_region()
{
  super::leaves_active_region();

  if ( get_current_action_name() == "dead" )
    kill();
} // armor::leaves_active_region()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture filename for counted item class.
 */
std::string ptb::armor::get_picture_filename() const
{
  return "";
} // armor::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture name for counted item class.
 */
std::string ptb::armor::get_picture_name() const
{
  return "";
} // armor::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text for notification.
 */
std::string ptb::armor::get_notification_text() const
{
  return "armor carnage";
} // armor::get_notification_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state idle.
 */
void ptb::armor::progress_idle( bear::universe::time_type elapsed_time )
{
  if ( scan(s_scan_wait_distance, false) )
    start_model_action("wake_up");
} // armor::progress_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state wake_up.
 */
void ptb::armor::progress_wake_up( bear::universe::time_type elapsed_time )
{
  // do nothing
} // armor::progress_wake_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state attack.
 */
void ptb::armor::progress_attack( bear::universe::time_type elapsed_time )
{
  // do nothing
} // armor::progress_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state punch.
 */
void ptb::armor::progress_punch( bear::universe::time_type elapsed_time )
{
  // do nothing
} // armor::progress_punch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state walk.
 */
void ptb::armor::progress_walk( bear::universe::time_type elapsed_time )
{
  if ( (!m_has_axe) && (!m_has_head) &&
       ( get_current_action_name() != "walk_without_head" ) )
    start_model_action("walk_without_head");

  if (  m_has_axe && scan(s_scan_axe_distance, true) )
    {
      set_speed( bear::universe::speed_type(0, 0) );
      set_internal_force(bear::universe::force_type(0, 0));
      set_external_force(bear::universe::force_type(0, 0));
      start_model_action("attack");
    }
  else
    {
      if ( get_center_of_mass().distance(m_origin_position) > m_max_distance )
        get_rendering_attributes().mirror
          (get_center_of_mass().x > m_origin_position.x);

      if ( get_rendering_attributes().is_mirrored() )
        add_internal_force( -m_walk_force );
      else
        add_internal_force( m_walk_force );

      if ( (!m_has_axe) && (m_has_head) )
        if ( scan(s_scan_punch_distance, true) )
          start_model_action("punch");
    }
} // armor::progress_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state dead.
 */
void ptb::armor::progress_dead( bear::universe::time_type elapsed_time )
{
  if (  has_bottom_contact() )
    {
      bear::visual::animation soul_anim
        ( get_level_globals().get_animation
          ("animation/forest/gorilla/gorilla_soul.canim") );
      create_headstone( get_bottom_middle(), soul_anim, s_soul_energy,
                        get_z_position() - 2 );
      kill();
    }
  else
    get_rendering_attributes().set_angle
      ( get_rendering_attributes().get_angle() - 0.1 );
} // armor::progress_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start idle state.
 */
void ptb::armor::start_idle()
{
  m_progress = &armor::progress_idle;
} // armor::start_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to wake up.
 */
void ptb::armor::start_wake_up()
{
  m_progress = &armor::progress_wake_up;
} // armor::start_wake_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to attack.
 */
void ptb::armor::start_attack()
{
  m_offensive_coefficients[indefensible_attack] = 0;
  m_progress = &armor::progress_attack;
} // armor::start_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to punch.
 */
void ptb::armor::start_punch()
{
  m_progress = &armor::progress_punch;
  m_offensive_coefficients[indefensible_attack] = 1;
} // armor::start_punch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start dead state.
 */
void ptb::armor::start_dead()
{
  if ( get_current_action_name() != "dead" )
    {
      start_model_action("dead");
      m_progress = &armor::progress_dead;
    }
} // armor::start_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to walk.
 */
void ptb::armor::start_walk()
{
  m_progress = &armor::progress_walk;
  m_offensive_coefficients[indefensible_attack] = 0;
} // armor::start_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create and throw the axe.
 */
void ptb::armor::create_axe()
{
  if ( m_has_axe )
    {
      bear::engine::model_mark_placement m;

      if ( get_mark_placement("axe", m) )
        {
          m_has_axe = false;
          const bear::universe::position_type pos(m.get_position());
          bear::universe::force_type force;

          force.x = 800000;
          if ( get_rendering_attributes().is_mirrored() )
            force.x *= -1;
          force.y = 0;

          axe* new_axe = new axe();

          CLAW_ASSERT(new_axe->is_valid(),
                      "The axe isn't correctly initialized" );

          new_item( *new_axe );

          new_axe->add_external_force(force);
          new_axe->set_center_of_mass(pos);
          new_axe->set_z_position( m.get_depth_position() );
          new_axe->get_rendering_attributes().set_angle(m.get_angle());

          set_global_substitute("axe", new bear::visual::animation() );
        }
    }
} // armor::create_axe()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create and throw the head.
 * \param right_orientation Indicates if the head must be throw on the right.
 */
void ptb::armor::create_head(bool right_orientation)
{
  if ( m_has_head )
    {
      bear::engine::model_mark_placement m;

      if ( get_mark_placement("head", m) )
        {
          bear::visual::animation anim
            (get_level_globals().auto_sprite
             ("gfx/castle/armor/armor-parts.png", "profile - head" ));
          m_has_head = false;
          const bear::universe::position_type pos(m.get_position());
          bear::universe::force_type force;

          force.x = 20000;
          if ( right_orientation )
            force.x *= -1;
          force.y = 10000;

          bear::decorative_item* new_head = new bear::decorative_item;

          CLAW_ASSERT(new_head->is_valid(),
                      "The head isn't correctly initialized" );

          new_item( *new_head );

          new_head->set_size(m.get_size());
          new_head->set_animation(anim);
          new_head->set_gap((m.get_size()-anim.get_max_size())/2);
          new_head->set_phantom(false);
          new_head->set_artificial(false);
          new_head->set_can_move_items(false);
          new_head->set_kill_on_contact(false);
          new_head->set_mass(1);
          new_head->set_elasticity(0.8);
          new_head->set_free_system(true);
          new_head->add_external_force(force);
          new_head->set_center_of_mass(pos);
          new_head->set_z_position( m.get_depth_position() + 100 );
          new_head->get_rendering_attributes().set_angle(m.get_angle());
          new_head->set_auto_angular_speed_factor(0.02);
          new_head->set_system_angle_as_visual_angle(true);

          set_global_substitute("head", new bear::visual::animation() );
        }
    }
} // armor::create_head()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan if there is a player in armor's direction.
 * \param distance The distance of scan.
 * \param only_main_direction Indicates if we scan only in the main direction.
 */
bool ptb::armor::scan
( bear::universe::coordinate_type distance, bool only_main_direction )
{
  bool result = false;

  player_proxy p1 = util::find_player( get_level_globals(), 1 );
  player_proxy p2 = util::find_player( get_level_globals(), 2 );

  if( p1 != NULL )
    {
      result =
          scan_for_player
          (p1, get_rendering_attributes().is_mirrored(), distance);

      if ( (!result) && (!only_main_direction) )
        {
          result =
            scan_for_player
            (p1, !get_rendering_attributes().is_mirrored(), distance);
          if ( result )
            get_rendering_attributes().mirror
              (!get_rendering_attributes().is_mirrored());
        }
    }

  if ( !result && (p2 != NULL) )
    {
      result =
        scan_for_player
        (p2, get_rendering_attributes().is_mirrored(), distance);

      if ( (!result) && (!only_main_direction) )
        {
          result =
            scan_for_player
            (p2, !get_rendering_attributes().is_mirrored(), distance);
          if ( result )
            get_rendering_attributes().mirror
              (!get_rendering_attributes().is_mirrored());
        }
    }

  return result;
} // armor::scan()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if a player is visible for the armor.
 * \param p The player we are looking for.
 * \param left_orientation True if the orientation is toward the left.
 * \param distance The distance of scan.
 */
bool ptb::armor::scan_for_player
( const player_proxy& p, bool left_orientation,
  bear::universe::coordinate_type distance ) const
{
  bool result = false;
  const bool player_on_the_left
    ( p.get_horizontal_middle() <= get_horizontal_middle() );

  if ( !(player_on_the_left ^ left_orientation) )
    {
      bear::engine::model_mark_placement m;
      m.set_position( get_center_of_mass() );
      get_mark_placement("eyes", m);
      bear::universe::position_type pos(p.get_bottom_middle());
      pos.y += 1;

      result = scan_no_wall_in_direction
        ( m.get_position(), pos - m.get_position(), distance );
    }

  return result;
} // armor::scan_in_direction()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan if there is a player in a given direction.
 * \param origin The position from which we start watching.
 * \param dir The direction in which the armor looks.
 * \param distance The distance of scan.
 */
bool ptb::armor::scan_no_wall_in_direction
( const bear::universe::position_type& origin,
  const bear::universe::vector_type& dir,
  bear::universe::coordinate_type distance ) const
{
  bear::universe::item_picking_filter filter;
  filter.set_can_move_items_value(true);

  if ( ( dir.length() <= distance ) && get_layer().has_world() )
    return
      get_layer().get_world().pick_item_in_direction
      (origin, dir, filter) == NULL;
  else
    return false;
} // armor::scan_no_wall_in_direction()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item on the snout.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::armor::on_hand_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  monster* other = dynamic_cast<monster*>(&that);

  if ( other != NULL )
    other->attack(*this);

  attack(that);
} // armor::on_hand_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item on the snout.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::armor::on_head_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  bear::engine::model_mark_placement m;

  if ( m_has_head )
    {
      monster* other = dynamic_cast<monster*>(&that);

      if ( other != NULL )
        if ( other->is_in_offensive_phase() )
          {
            m_walk_force *= 3;
            create_head
              ( info.get_collision_side() ==
                bear::universe::zone::middle_right_zone);
            if ( m_has_axe )
              start_model_action("attack");
          }
    }
} // armor::on_head_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void ptb::armor::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "state: " << get_current_action_name() << "\n";
  oss << "origin_position: " << m_origin_position.x << " " <<
    m_origin_position.y << "\n";

  str += oss.str();
} // armor::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::armor::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::armor, start_attack, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::armor, start_punch, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::armor, start_idle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::armor, start_wake_up, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::armor, start_walk, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::armor, start_dead, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::armor, create_axe, void );
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( armor, on_hand_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( armor, on_head_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
} // armor::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::armor )
