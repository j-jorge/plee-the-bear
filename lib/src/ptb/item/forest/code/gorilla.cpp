/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::gorilla class.
 * \author S�bastien Angibaud
 */
#include "ptb/item/forest/gorilla.hpp"

#include "ptb/util/player_util.hpp"

#include "generic_items/camera_shaker.hpp"
#include "engine/world.hpp"

#include "engine/export.hpp"

#include <claw/assert.hpp>

BASE_ITEM_EXPORT( gorilla, ptb )

const unsigned int ptb::gorilla::s_soul_energy = 30;
const unsigned int ptb::gorilla::s_listen_distance = 200;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::gorilla::gorilla()
  : m_progress(NULL), m_want_come_back(false), m_scan_distance(320)
{
  set_z_fixed(false);
  set_mass(100);
  set_density(2);

  m_monster_type = monster::enemy_monster;
  m_energy = 30;
  m_offensive_phase = true;
  m_offensive_force = s_gorilla_offensive_force;
  m_offensive_coefficients[normal_attack] = 1;
  get_rendering_attributes().mirror(false);
  set_category("gorilla");
} // gorilla::gorilla()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::gorilla::~gorilla()
{
} // gorilla::~gorilla()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::gorilla::pre_cache()
{
  get_level_globals().load_animation
    ("animation/forest/gorilla/gorilla_soul.canim");
  get_level_globals().load_model("model/forest/gorilla.cm");
  get_level_globals().load_model("model/headstone.cm");
} // gorilla::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::gorilla::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/forest/gorilla.cm") );
  start_model_action("idle");
  m_progress = &gorilla::progress_idle;
} // gorilla::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::gorilla::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // gorilla::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::gorilla::inform_no_energy(const monster& attacker)
{
  m_is_injured = false;

  if ( get_current_action_name() != "dead" )
    {
      start_dead();
      die(attacker);
    }
} // gorilla::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::gorilla::leaves_active_region()
{
  super::leaves_active_region();

  if ( get_current_action_name() == "dead" )
    kill();
} // gorilla::leaves_active_region()

/*----------------------------------------------------------------------------*/
/**
 * \brief The monster is injure.
 * \param attacker The monster attacking me.
 * \param side The side on which I am attacked.
 * \param duration The duration of injure state.
 */
void ptb::gorilla::injure
( const monster& attacker, bear::universe::zone::position side,
  double duration )
{
  if ( ( get_current_action_name() == "idle" ) ||
       ( get_current_action_name() == "scan_left" ) ||
       ( get_current_action_name() == "scan_right" ) ||
       ( get_current_action_name() == "come_back" ) )
    {
      m_scan_distance= 500;
      choose_angry_action();

      const base_item* m = dynamic_cast<const base_item*>(&attacker);

      if ( m != NULL )
        {
          if ( m->get_speed().x > 0 )
            get_rendering_attributes().mirror(true);
          else
            get_rendering_attributes().mirror(false);
        }
    }

  super::injure(attacker, side, duration);
} // ptb::gorilla::injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell is the item has a defensive power.
 * \param index Index of the power.
 * \param attacker The attacker.
 * \param side The side on which the power is checked.
 */
bool ptb::gorilla::get_defensive_power_by_side
( unsigned int index, const monster& attacker,
  bear::universe::zone::position side ) const
{
  bool result = super::get_defensive_power_by_side(index, attacker, side);

  if ( !result )
    {
      if ( side == bear::universe::zone::middle_zone )
        {
          if ( get_current_action_name() == "come_back" )
            {
              const base_item* item = dynamic_cast<const base_item*>(&attacker);
              if ( ( item != NULL ) &&
                   get_rendering_attributes().is_mirrored() )
                {
                  if ( item->get_left() >= get_left() )
                    result = 0;
                }
              else if ( item->get_right() <= get_right() )
                result = 0;
            }
          else
            result = true;
        }
      else if ( get_current_action_name() == "attack" )
        {
          if ( get_rendering_attributes().is_mirrored() )
            result = ( side == bear::universe::zone::middle_left_zone );
          else
            result = ( side == bear::universe::zone::middle_right_zone );
        }
      else if ( ( get_current_action_name() == "angry_1" )
                || ( get_current_action_name() == "angry_2" )
                || ( get_current_action_name() == "angry_3" ) )
        result = true;
    }

  return result;
} // gorilla::get_defensive_power_by_side()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the offensive coefficient for a given attacked item and a given
 *        side.
 * \param index The index of the coefficient.
 * \param other The attacked monster.
 * \param side The side of this through which the attack is done.
 */
unsigned int ptb::gorilla::get_offensive_coefficient
( unsigned int index, const monster& other,
  bear::universe::zone::position side ) const
{
  unsigned int result;

  if ( get_current_action_name() == "come_back" )
    result = get_offensive_coefficient_come_back(index, other, side);
  else if ( get_current_action_name() == "attack" )
    result = get_offensive_coefficient_attack(index, other, side);
  else if ( get_current_action_name() == "angry" )
    result = get_offensive_coefficient_angry(index, other, side);
  else
    {
      result = super::get_offensive_coefficient(index, other, side);

      if ( ( index == indefensible_attack ) || ( index == normal_attack ) )
        {
          unsigned int result_attack;
          if ( index == indefensible_attack )
            result_attack = 1;
          else
            result_attack = 0;

          if ( side == bear::universe::zone::middle_zone )
            {
              if ( m_is_injured )
                result = 0;
              else
                result = result_attack;
            }
        }
    }

  return result;
} // gorilla::get_offensive_coefficient()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::gorilla::has_attacked(const monster& other)
{
  if ( other.get_monster_type() == monster::player_monster )
    if ( get_current_action_name() == "attack" )
      {
        set_speed(bear::universe::speed_type(0, 0));
        m_want_come_back = true;
      }
} // gorilla::has_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture filename for counted item class.
 */
std::string ptb::gorilla::get_picture_filename() const
{
  return "gfx/forest/bonus-icons/bonus-icons.png";
} // gorilla::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture name for counted item class.
 */
std::string ptb::gorilla::get_picture_name() const
{
  return "gorilla";
} // gorilla::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text for notification.
 */
std::string ptb::gorilla::get_notification_text() const
{
  return "gorilla carnage";
} // gorilla::get_notification_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state idle.
 */
void ptb::gorilla::progress_idle( bear::universe::time_type elapsed_time )
{
  if ( listen() )
    choose_angry_action();
} // gorilla::progress_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state attack.
 */
void ptb::gorilla::progress_attack( bear::universe::time_type elapsed_time )
{
  if ( m_want_come_back )
    start_model_action("come_back");
  else if ( !scan(get_rendering_attributes().is_mirrored(), m_scan_distance) )
    m_want_come_back = true;
  else if ( get_rendering_attributes().is_mirrored() )
    add_internal_force( bear::universe::force_type(-250000, 0) );
  else
    add_internal_force( bear::universe::force_type(250000, 0) );
} // gorilla::progress_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state angry.
 */
void ptb::gorilla::progress_angry( bear::universe::time_type elapsed_time )
{
  // do nothing
} // gorilla::progress_angry()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state dead.
 */
void ptb::gorilla::progress_dead( bear::universe::time_type elapsed_time )
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
} // gorilla::progress_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state scan_left.
 */
void ptb::gorilla::progress_scan_left( bear::universe::time_type elapsed_time )
{
  if ( m_want_scan )
    {
      if ( listen() )
        choose_angry_action();
      else if ( scan( !get_rendering_attributes().is_mirrored(),
                      m_scan_distance ) )
        {
          choose_angry_action();
          get_rendering_attributes().mirror
            (!get_rendering_attributes().is_mirrored());
        }
    }
} // gorilla::progress_scan_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state scan_right.
 */
void ptb::gorilla::progress_scan_right(bear::universe::time_type elapsed_time)
{
  if ( m_want_scan )
    {
      if ( listen() )
        choose_angry_action();
      else if ( scan( get_rendering_attributes().is_mirrored(),
                      m_scan_distance) )
        choose_angry_action();
    }
} // gorilla::progress_scan_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state scome_back.
 */
void ptb::gorilla::progress_come_back(bear::universe::time_type elapsed_time)
{
  get_rendering_attributes().mirror(get_left() >= m_origin_position.x );

  if ( scan(get_rendering_attributes().is_mirrored(), m_scan_distance) )
    choose_angry_action();
  else if ( std::abs(get_left() - m_origin_position.x) < 10 )
    start_model_action("idle");
  else if ( has_right_contact() || has_left_contact() )
    start_model_action("idle");
  else if ( get_rendering_attributes().is_mirrored() )
    add_internal_force( bear::universe::force_type(-70000, 0) );
  else
    add_internal_force( bear::universe::force_type(70000, 0) );
} // gorilla::progress_come_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start idle state.
 */
void ptb::gorilla::start_idle()
{
  m_scan_distance = 320;
  m_progress = &gorilla::progress_idle;
  m_origin_position = get_bottom_left();
} // gorilla::start_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to attack.
 */
void ptb::gorilla::start_attack()
{
  m_want_come_back = false;
  m_progress = &gorilla::progress_attack;
} // gorilla::start_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start dead state.
 */
void ptb::gorilla::start_dead()
{
  if ( get_current_action_name() != "dead" )
    {
      start_model_action("dead");
      m_progress = &gorilla::progress_dead;
    }
} // gorilla::start_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to angry.
 */
void ptb::gorilla::start_angry()
{
  m_progress = &gorilla::progress_angry;
} // gorilla::start_angry()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to scan left area.
 */
void ptb::gorilla::start_scan_left()
{
  m_want_scan = false;
  m_progress = &gorilla::progress_scan_left;
} // gorilla::start_scan_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to scan right area.
 */
void ptb::gorilla::start_scan_right()
{
  m_want_scan = false;
  m_progress = &gorilla::progress_scan_right;
} // gorilla::start_scan_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to scan.
 */
void ptb::gorilla::start_scan()
{
  m_want_scan = true;
} // gorilla::start_scan()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to come back.
 */
void ptb::gorilla::start_come_back()
{
  m_scan_distance = 320;
  m_progress = &gorilla::progress_come_back;
} // gorilla::start_come_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Listen if there is a player in the accessive zone.
 */
bool ptb::gorilla::listen()
{
  bool result = false;

  if ( scan(false, s_listen_distance) )
    {
      result = true;
      get_rendering_attributes().mirror(false);
    }
  else if ( scan(true, s_listen_distance) )
    {
      result = true;
      get_rendering_attributes().mirror(true);
    }

  return result;
} // gorilla::listen()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan if there is a player in a given direction.
 * \param left_orientation True if the orientation is toward the left.
 * \param distance The distance of scan.
 */
bool ptb::gorilla::scan
( bool left_orientation, bear::universe::coordinate_type distance ) const
{
  bool result = false;

  player_proxy p1 = util::find_player( get_level_globals(), 1 );
  player_proxy p2 = util::find_player( get_level_globals(), 2 );

  if( p1 != NULL )
    result =
      scan_for_player(p1, left_orientation, distance);

  if ( !result && (p2 != NULL) )
    result =
      scan_for_player(p2, left_orientation, distance);

  return result;
} // gorilla::scan()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if a player is visible for the gorilla.
 * \param p The player we are looking for.
 * \param left_orientation True if the orientation is toward the left.
 * \param distance The distance of scan.
 */
bool ptb::gorilla::scan_for_player
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
} // gorilla::scan_in_direction()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan if there is a player in a given direction.
 * \param origin The position from which we start watching.
 * \param dir The direction in which the gorilla looks.
 * \param distance The distance of scan.
 */
bool ptb::gorilla::scan_no_wall_in_direction
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
} // gorilla::scan_no_wall_in_direction()

/*----------------------------------------------------------------------------*/
/**
 * \brief Choose an angry action.
 */
void ptb::gorilla::choose_angry_action()
{
  std::ostringstream s;
  s << "angry_" << (rand() % 3 + 1);
  start_model_action(s.str());
} // gorilla::choose_angry_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Shake the camera.
 */
void ptb::gorilla::hit()
{
  bear::camera_shaker::shake_around( *this, 20, 0.2 );
} // gorilla::hit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a given offensive coefficient in the state "attack".
 * \param index The index of the attack.
 * \param other The other monster.
 * \param side The side of this through which the attack is done.
 */
unsigned int ptb::gorilla::get_offensive_coefficient_attack
( unsigned int index, const monster& other,
  bear::universe::zone::position side ) const
{
  // The gorilla always attack on the front in attack_state.
  unsigned int result = super::get_offensive_coefficient(index, other, side);

  if ( ( index == indefensible_attack ) || ( index == normal_attack ) )
     {
       unsigned int result_attack;
       if ( index == indefensible_attack )
         result_attack = 1;
       else
         result_attack = 0;

       if ( side == bear::universe::zone::middle_zone )
         {
           if ( m_is_injured )
             result = 0;
           else
             result = result_attack;
         }
       else if ( get_rendering_attributes().is_mirrored() )
         {
           if ( side == bear::universe::zone::middle_left_zone )
             result = result_attack;
         }
       else if ( side == bear::universe::zone::middle_right_zone )
         result = result_attack;
     }

  return result;
} // gorilla::get_offensive_coefficient_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a given offensive coefficient in a state "angry".
 * \param index The index of the attack.
 * \param other The other monster.
 * \param side The side of this through which the attack is done.
 */
unsigned int ptb::gorilla::get_offensive_coefficient_angry
( unsigned int index, const monster& other,
  bear::universe::zone::position side ) const
{
  // The gorilla always attack in angry_state.
  unsigned int result = super::get_offensive_coefficient(index, other, side);

  if ( ( index == indefensible_attack ) || ( index == normal_attack ) )
     {
       unsigned int result_attack;
       if ( index == indefensible_attack )
         result_attack = 1;
       else
         result_attack = 0;

       if ( side == bear::universe::zone::middle_zone )
         {
           if ( m_is_injured )
             result = 0;
           else
             result = result_attack;
         }
       else
         result = result_attack;
     }

  return result;
} // gorilla::get_offensive_coefficient_angry()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a given offensive coefficient on the state "come_back".
 * \param index The index of the attack.
 * \param other The other monster.
 * \param side The side of this through which the attack is done.
 */
unsigned int ptb::gorilla::get_offensive_coefficient_come_back
( unsigned int index, const monster& other,
  bear::universe::zone::position side ) const
{
  // The gorilla attacks forward in come_back state.
  unsigned int result = super::get_offensive_coefficient(index, other, side);

  if ( ( index == indefensible_attack ) || ( index == normal_attack ) )
     {
       if ( side == bear::universe::zone::middle_zone )
         {
           if ( m_is_injured )
             result = 0;
           else
             {
               const base_item* item = dynamic_cast<const base_item*>(&other);
               if ( ( item != NULL ) &&
                    get_rendering_attributes().is_mirrored() )
                 {
                   if ( item->get_left() >= get_left() )
                     result = 0;
                 }
               else if ( item->get_right() <= get_right() )
                 result = 0;
             }
         }
       else
         {
           const base_item* item = dynamic_cast<const base_item*>(&other);
           if ( ( item != NULL ) &&
                get_rendering_attributes().is_mirrored() )
             {
               if ( item->get_left() >= get_left() )
                 result = 0;
             }
           else if ( item->get_right() <= get_right() )
             result = 0;
         }
     }

  return result;
} // gorilla::get_offensive_coefficient_come_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void ptb::gorilla::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "state: " << get_current_action_name() << "\n";
  oss << "origin_position: " << m_origin_position.x << " " <<
    m_origin_position.y << "\n";

  str += oss.str();
} // gorilla::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::gorilla::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, start_scan_left, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, start_scan_right, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, start_scan, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, start_attack, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, start_idle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, start_angry, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, start_dead, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, start_come_back, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::gorilla, hit, void );
} // gorilla::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::gorilla )
