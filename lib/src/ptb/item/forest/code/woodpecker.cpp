/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::woodpecker class.
 * \author S�bastien Angibaud
 */
#include "ptb/item/forest/woodpecker.hpp"

#include "ptb/util/player_util.hpp"

#include "universe/forced_movement/forced_join.hpp"
#include "universe/forced_movement/forced_goto.hpp"
#include "universe/forced_movement/forced_sequence.hpp"
#include "universe/forced_movement/forced_tracking.hpp"
#include "universe/forced_movement/forced_stay_around.hpp"
#include "engine/export.hpp"
#include <claw/assert.hpp>
#include "engine/game.hpp"

BASE_ITEM_EXPORT( woodpecker, ptb )

const unsigned int ptb::woodpecker::s_soul_energy = 30;
const unsigned int ptb::woodpecker::s_listen_distance = 380;
const unsigned int ptb::woodpecker::s_scan_distance = 300;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::woodpecker::woodpecker()
  : m_progress(NULL)
{
  set_z_fixed(false);
  set_mass(50);
  set_density(2);

  m_monster_type = monster::enemy_monster;
  m_energy = 20;
  m_offensive_phase = true;
  m_offensive_force = s_woodpecker_offensive_force;
  m_offensive_coefficients[normal_attack] = 1;
  get_rendering_attributes().mirror(false);
  set_category("woodpecker");
} // woodpecker::woodpecker()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::woodpecker::~woodpecker()
{
} // woodpecker::~woodpecker()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::woodpecker::pre_cache()
{
  get_level_globals().load_animation
    ("animation/forest/woodpecker/woodpecker_soul.canim");
  get_level_globals().load_image
    ("gfx/forest/woodpecker/woodpecker-1.png");
  get_level_globals().load_model("model/forest/woodpecker.cm");
  get_level_globals().load_model("model/headstone.cm");
  get_level_globals().load_sound("sound/forest/woodpecker/peck.ogg");
} // woodpecker::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::woodpecker::on_enters_layer()
{
  super::on_enters_layer();

  m_origin_item = new bear::reference_item();
  m_origin_item->set_center_of_mass(get_center_of_mass());
  new_item( *m_origin_item );
  m_origin_item->set_artificial(true);

  m_attack_item = new bear::reference_item();
  m_attack_item->set_bottom_left(get_bottom_left());
  new_item( *m_attack_item );
  m_attack_item->set_artificial(true);

  set_model_actor
    ( get_level_globals().get_model("model/forest/woodpecker.cm") );

  m_origin_orientation = get_rendering_attributes().is_mirrored();
  start_model_action("peck");
  m_progress = &woodpecker::progress_peck;
  search_players();
  set_system_angle_as_visual_angle(true);
} // woodpecker::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::woodpecker::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );
  search_players();

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // woodpecker::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::woodpecker::inform_no_energy(const monster& attacker)
{
  m_is_injured = false;

  if ( get_current_action_name() != "dead" )
    {
      start_dead();
      die(attacker);
    }
} // woodpecker::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::woodpecker::leaves_active_region()
{
  super::leaves_active_region();

  if ( get_current_action_name() == "dead" )
    kill();
} // woodpecker::leaves_active_region()

/*----------------------------------------------------------------------------*/
/**
 * \brief The monster is injure.
 * \param attacker The monster attacking me.
 * \param side The side on which I am attacked.
 * \param duration The duration of the injure state.
 */
void ptb::woodpecker::injure
( const monster& attacker, bear::universe::zone::position side,
  double duration )
{
  if ( ( get_current_action_name() == "peck" ) ||
       ( get_current_action_name() == "scan" ) )
    {
      start_model_action("attack");

      if ( ( side == bear::universe::zone::middle_left_zone )
          || ( side == bear::universe::zone::top_left_zone )
          || ( side == bear::universe::zone::bottom_left_zone ) )
        get_rendering_attributes().mirror(true);
      else
        get_rendering_attributes().mirror(false);
    }

  super::injure(attacker, side, duration);
} // ptb::woodpecker::injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell is the item has a defensive power.
 * \param index Index of the power.
 * \param attacker The attacker.
 * \param side The side on which the power is checked.
 */
bool ptb::woodpecker::get_defensive_power_by_side
( unsigned int index, const monster& attacker,
  bear::universe::zone::position side ) const
{
  bool result = super::get_defensive_power_by_side(index, attacker, side);

  if ( !result )
    {
      if ( side == bear::universe::zone::middle_zone )
        result = true;
      else
        {
          if ( get_current_action_name() == "attack" )
            {
              if ( get_rendering_attributes().is_mirrored() )
                result =
                  ( side == bear::universe::zone::middle_left_zone )
                  || ( side == bear::universe::zone::top_zone );
              else
                result =
                  ( side == bear::universe::zone::middle_right_zone )
                  || ( side == bear::universe::zone::top_zone );
            }
        }
    }

  return result;
} // woodpecker::get_defensive_power_by_side()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the offensive coefficient for a given attacked item and a given
 *        side.
 * \param index The index of the coefficient.
 * \param attacked The attacked monster.
 * \param side The side of this through which the attack is done.
 */
unsigned int ptb::woodpecker::get_offensive_coefficient
( unsigned int index, const monster& attacked,
  bear::universe::zone::position side ) const
{
  unsigned int result = super::get_offensive_coefficient(index, attacked, side);

  if ( ( index == indefensible_attack ) || ( index == normal_attack ) )
    {
      bool ok = false;
      if ( side == bear::universe::zone::middle_zone )
        ok = true;
      else if ( get_current_action_name() == "attack" )
        {
          if ( get_rendering_attributes().is_mirrored() )
            {
              if ( ( side == bear::universe::zone::middle_left_zone )
                  || ( side == bear::universe::zone::bottom_zone ) )
                ok = true;
            }
          else if ( ( side == bear::universe::zone::middle_right_zone )
              || ( side == bear::universe::zone::bottom_zone ) )
            ok = true;
        }

      if ( ok )
        {
          if ( index == indefensible_attack )
            result = 1;
          else
            result = 0;
        }
    }

  return result;
} // woodpecker::get_offensive_coefficient()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::woodpecker::has_attacked(const monster& other)
{
  if ( get_current_action_name() == "attack" )
    {
      join_origin();
      if ( !get_rendering_attributes().is_flipped() )
        get_rendering_attributes().mirror(true);
      get_rendering_attributes().flip(false);
      start_model_action("come_back");
    }
} // woodpecker::has_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture filename for counted item class.
 */
std::string ptb::woodpecker::get_picture_filename() const
{
  return "gfx/forest/bonus-icons/bonus-icons.png";
} // woodpecker::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture name for counted item class.
 */
std::string ptb::woodpecker::get_picture_name() const
{
  return "woodpecker";
} // woodpecker::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text for notification.
 */
std::string ptb::woodpecker::get_notification_text() const
{
  return "woodpecker carnage";
} // woodpecker::get_notification_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state idle.
 */
void ptb::woodpecker::progress_peck( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);
  bool left_orientation;

  if ( listen(left_orientation) )
    {
      if ( left_orientation )
        if ( m_origin_orientation )
          start_model_action("scan_right");
        else
          start_model_action("scan_left");
      else if ( m_origin_orientation )
        start_model_action("scan_left");
      else
        start_model_action("scan_right");
    }
}// woodpecker::progress_peck()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state attack.
 */
void ptb::woodpecker::progress_attack( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);
  
  if ( get_forced_movement().is_finished() )
    {
      join_origin();

      if ( !get_rendering_attributes().is_flipped() )
        get_rendering_attributes().mirror(true);

      get_rendering_attributes().flip(false);
      start_model_action("come_back");
    }
} // woodpecker::progress_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state dead.
 */
void ptb::woodpecker::progress_dead( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if (  has_bottom_contact() )
    {
      bear::visual::animation soul_anim
        ( get_level_globals().get_animation
          ("animation/forest/woodpecker/woodpecker_soul.canim") );
      create_headstone( get_bottom_middle(), soul_anim, s_soul_energy,
                        get_z_position() - 2 );
      kill();
    }
  else
    get_rendering_attributes().set_angle
      ( get_rendering_attributes().get_angle() - 0.1 );
} // woodpecker::progress_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state scan.
 */
void ptb::woodpecker::progress_scan( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);
  unsigned int index;
  bool left_orientation;

  if ( scan(s_scan_distance, index, left_orientation) )
    {
      get_rendering_attributes().mirror(!left_orientation);
      clear_forced_movement();
      create_attack_movement(index);
      start_model_action("attack");
    }
  else if ( !listen(left_orientation) )
    start_model_action("peck");
} // woodpecker::progress_scan()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state come_back.
 */
void ptb::woodpecker::progress_come_back
(bear::universe::time_type elapsed_time)
{
  super::progress(elapsed_time);

  if ( get_forced_movement().is_finished() )
    {
      get_rendering_attributes().mirror(m_origin_orientation);
      start_model_action("peck");
    }
} // woodpecker::progress_come_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start peck state.
 */
void ptb::woodpecker::start_peck()
{
  get_rendering_attributes().set_angle(0);
  set_system_angle(0);
  clear_forced_movement();
  set_center_of_mass(m_origin_item->get_center_of_mass());
  m_progress = &woodpecker::progress_peck;

  bear::universe::forced_tracking mvt
    (std::numeric_limits<bear::universe::time_type>::infinity());
  mvt.set_reference_point_on_center(*m_origin_item);
  mvt.set_distance(bear::universe::position_type(0,0));

  set_forced_movement(mvt);
} // woodpecker::start_peck()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to attack.
 */
void ptb::woodpecker::start_attack()
{
  get_rendering_attributes().mirror(false);
  m_progress = &woodpecker::progress_attack;
} // woodpecker::start_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start dead state.
 */
void ptb::woodpecker::start_dead()
{
  get_rendering_attributes().set_angle(0);
  set_system_angle(0);
  if ( get_current_action_name() != "dead" )
    {
      clear_forced_movement();
      m_origin_item->kill();
      m_attack_item->kill();
      start_model_action("dead");
      m_progress = &woodpecker::progress_dead;
      create_feathers();
      create_wig();
    }
} // woodpecker::start_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to scan area.
 */
void ptb::woodpecker::start_scan()
{
  get_rendering_attributes().set_angle(0);
  set_system_angle(0);
  m_progress = &woodpecker::progress_scan;
} // woodpecker::start_scan()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to come back.
 */
void ptb::woodpecker::start_come_back()
{
  get_rendering_attributes().set_angle(0);
  set_system_angle(0);
  m_progress = &woodpecker::progress_come_back;
} // woodpecker::start_come_back()

/*---------------------------------------------------------------------------*/
/**
 * \brief Listen if there is a player in the accessive zone.
 * \param left_orientation True if the orientation is on the left.
 */
bool ptb::woodpecker::listen(bool& left_orientation)
{
  unsigned int index;

  return scan(s_listen_distance, index, left_orientation);
} // woodpecker::listen()

/*---------------------------------------------------------------------------*/
/**
 * \brief Scan if there is a player in a given direction.
 * \param left_orientation True if the orientation is on the left.
 * \param distance The distance of scan.
 * \param index The index of the player found.
 * \param left_orientation Indicates if the player is in the left.
 */
bool ptb::woodpecker::scan
( bear::universe::coordinate_type distance,
  unsigned int& index, bool& left_orientation) const
{
  bool result = false;

  if(m_first_player != NULL)
    {
      if ( m_first_player.get_bottom() <= get_top() )
        {
          result =
            m_first_player.get_center_of_mass().distance( get_center_of_mass() )
            < distance;
          index = 1;
          left_orientation =
            m_first_player.get_center_of_mass().x <= get_center_of_mass().x;
        }
    }

  if ( !result && (m_second_player != NULL) )
    {
      if ( m_second_player.get_bottom() <= get_top() )
        {
          result =
            m_second_player.get_center_of_mass().distance
            ( get_center_of_mass() ) < distance;
          index = 2;
          left_orientation =
            m_second_player.get_center_of_mass().x <= get_center_of_mass().x;
        }
    }

  return result;
} // woodpecker::scan()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search players.
 */
void ptb::woodpecker::search_players()
{
  if ( m_first_player == NULL )
    m_first_player = util::find_player( get_level_globals(), 1 );

  if ( m_second_player == NULL )
    m_second_player = util::find_player( get_level_globals(), 2 );
} // woodpecker::search_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the movement when the woodpecker attacks.
 * \param index The index of the player found.
 */
void ptb::woodpecker::create_attack_movement(unsigned int index)
{
  bear::universe::speed_type vect;

  if ( index == 1 )
    {
      m_attack_item->set_center_of_mass( m_first_player.get_center_of_mass() );
      vect = m_first_player.get_center_of_mass() - get_center_of_mass();
    }
  else
    {
      m_attack_item->set_center_of_mass( m_second_player.get_center_of_mass() );
      vect = m_second_player.get_center_of_mass() - get_center_of_mass();
    }

  set_system_angle(atan2(vect.y, vect.x));
  get_rendering_attributes().flip(vect.x<0);

  bear::universe::forced_join mvt_join(0.7);
  mvt_join.set_reference_point_on_center(*m_attack_item);

  set_forced_movement(mvt_join);
} // create_attack_movement()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the movement when the woodpecker comes back whithout attack.
 */
void ptb::woodpecker::join_origin()
{
  bear::universe::forced_join mvt(1);
  mvt.set_reference_point_on_center(*m_origin_item);

  set_forced_movement(mvt);
} // woodpecker::join_origin()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void ptb::woodpecker::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "state: ";
  if ( get_current_action_name() == "dead" )
    oss << "dead";
  else if ( get_current_action_name() == "peck" )
    oss << "peck";
  else if ( get_current_action_name() == "attack" )
    oss << "attack";
  else if ( get_current_action_name() == "come_back" )
    oss << "come_back";
  else if ( get_current_action_name() == "scan" )
    oss << "scan";
  oss << "\n";

  str += oss.str();
} // woodpecker::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the wig when the woodpecker dies.
 */
void ptb::woodpecker::create_wig()
{
  bear::engine::level_globals& glob = get_level_globals();
  bear::decorative_item* item = new bear::decorative_item;

  item->set_sprite
          (glob.auto_sprite("gfx/forest/woodpecker/woodpecker-1.png", "wig"));
  item->set_phantom(false);
  item->set_artificial(false);
  item->set_can_move_items(false);
  item->set_kill_on_contact(false);
  item->set_mass(0.001);
  item->set_friction(0.9);
  item->set_gap_y(-5);

  double r1=(double)rand()/(double)RAND_MAX;
  double r2=(double)rand()/(double)RAND_MAX;
  item->add_external_force
    (bear::universe::force_type(25*(r1-0.5), 25*(r2)));

  item->set_center_of_mass(get_center_of_mass());

  new_item( *item );
  CLAW_ASSERT( item->is_valid(),
                 "The wig of woodpecker isn't correctly initialized" );
} // woodpecker::create_wig()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create some feathers when the woodpecker dies.
 */
void ptb::woodpecker::create_feathers()
{
  for ( unsigned int i = 1; i != 10; ++i )
    create_feather();
} // woodpecker::create_feathers()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a feather when the woodpecker dies.
 */
void ptb::woodpecker::create_feather()
{
  // create reference
  bear::decorative_item* ref = new bear::decorative_item;
  set_feather_reference(ref);
  new_item( *ref );
  CLAW_ASSERT( ref->is_valid(),
               "The reference of feather of woodpecker isn't correctly "
               "initialized" );

  // create feather
  bear::decorative_item* item = new bear::decorative_item;
  set_feather(item);
  new_item( *item );
  CLAW_ASSERT( item->is_valid(),
                 "The feather of woodpecker isn't correctly initialized" );

  // create movement
  bear::universe::forced_stay_around mvt;
  mvt.set_max_angle( 0.2 );
  mvt.set_speed( 100 );
  mvt.set_max_distance( 200 );
  mvt.set_apply_angle( true );
  mvt.set_reference_point_on_center(*ref);
  mvt.set_auto_remove(true);
  mvt.set_item(*item);

  item->set_forced_movement( mvt );
} // woodpecker::create_feather()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the reference item for feather movement.
 * param ref The item to set.
 */
void ptb::woodpecker::set_feather_reference
(bear::decorative_item* ref)
{
  ref->set_phantom(false);
  ref->set_artificial(false);
  ref->set_can_move_items(false);
  ref->set_kill_on_contact(true);
  ref->set_mass(0.001);
  ref->set_friction(0.7);

  double r1=(double)rand()/(double)RAND_MAX;
  double r2=(double)rand()/(double)RAND_MAX;
  ref->add_external_force
    (bear::universe::force_type(25*(r1-0.5), 25*(r2)));

  ref->set_height(1);
  ref->set_width(1);
  ref->set_center_of_mass(get_center_of_mass());
} // woodpecker::set_feather_reference()


/*----------------------------------------------------------------------------*/
/**
 * \brief Set the feather.
 * param item The item to set.
 */
void ptb::woodpecker::set_feather(bear::decorative_item* item)
{
  bear::engine::level_globals& glob = get_level_globals();

  item->set_friction(0.7);

  double r = 3* ((double)rand() / (double)RAND_MAX);
  if ( r >= 2 )
    item->set_sprite
      (glob.auto_sprite("gfx/forest/woodpecker/woodpecker-1.png",
                        "main feather"));
  else if ( r >= 1 )
    item->set_sprite
      (glob.auto_sprite("gfx/forest/woodpecker/woodpecker-1.png",
                        "white feather"));
  else
    item->set_sprite
      (glob.auto_sprite("gfx/forest/woodpecker/woodpecker-1.png",
                        "red feather"));

  item->set_phantom(false);
  item->set_artificial(false);
  item->set_can_move_items(false);
  item->get_rendering_attributes().set_angle(get_visual_angle());
  item->set_kill_on_contact(false);
  item->set_z_position(get_z_position()+1);
  item->set_mass(0.001);
  item->set_center_of_mass(get_center_of_mass());
} // woodpecker::set_feather()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::woodpecker::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::woodpecker, start_peck, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::woodpecker, start_attack, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::woodpecker, start_dead, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::woodpecker, start_scan, void );
  TEXT_INTERFACE_CONNECT_METHOD_0
    ( ptb::woodpecker, start_come_back, void );
} // woodpecker::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::woodpecker )
