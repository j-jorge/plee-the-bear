/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::base_bonus class.
 * \author Sebastien Angibaud
 */
#include "ptb/item_brick/base_bonus.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/player_proxy.hpp"
#include "ptb/item/little_plee.hpp"
#include "ptb/defines.hpp"
#include "ptb/message/status_layer_notification_message.hpp"

#include "universe/collision_info.hpp"
#include "generic_items/decorative_item.hpp"

#include "engine/game.hpp"
#include "engine/export.hpp"

#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::base_bonus::base_bonus()
  : sniffable("bonus"), m_current_type(0), m_player_index(0),
    m_change_interval
    (std::numeric_limits<bear::universe::time_type>::infinity()),
    m_elapsed_time(0), m_stock(0), m_bonus_given(false)
{
  set_density(1.2);
} // base_bonus::base_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::base_bonus::build()
{
  super::build();

  m_current_type = ((double)rand() / ((double)RAND_MAX+1)) * m_type.size();

  do_set_type(m_type[m_current_type]);
} // base_bonus::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "unsigned integer".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::base_bonus::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if ( name == "base_bonus.player_index" )
    m_player_index = value;
  else
    result = super::set_u_integer_field(name,value);

  return result;
} // base_bonus::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::base_bonus::set_real_field( const std::string& name, double value )
{
  bool result = true;

  if ( name == "base_bonus.change_interval" )
    m_change_interval = std::max(0.0, value);
  else
    result = super::set_real_field( name, value );

  return result;
} // base_bonus::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "list of string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::base_bonus::set_string_list_field
( const std::string& name, const std::vector<std::string>& value )
{
  bool result = true;

  if ( name == "base_bonus.type" )
    for (std::size_t i=0; i!=value.size(); ++i)
      add_type( type_from_string(value[i]) );
  else
    result = super::set_string_list_field( name, value );

  return result;
} // base_bonus::set_string_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is well initialized.
 */
bool ptb::base_bonus::is_valid() const
{
  return !m_type.empty() && super::is_valid();
} // base_bonus::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void ptb::base_bonus::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  add_visual( m_animation, visuals );
} // base_bonus::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::base_bonus::progress( bear::universe::time_type elapsed_time )
{
  m_animation.next(elapsed_time);
  m_elapsed_time += elapsed_time;

  const std::size_t p
    ( std::size_t(m_elapsed_time / m_change_interval) % m_type.size() );

  if ( p!=m_current_type )
    {
      m_current_type = p;
      do_set_type( m_type[m_current_type] );
    }
} // base_bonus::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the bonus is given.
 */
bool ptb::base_bonus::get_bonus_given() const
{
  return m_bonus_given;
} // base_bonus::get_bonus_given

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the type of the bonus.
 */
ptb::base_bonus::base_bonus_type ptb::base_bonus::get_type() const
{
  if ( m_type.empty() )
    return unknown_type;
  else
    return m_type[m_current_type];
} // base_bonus::get_type()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the type of the bonus.
 * \param t The new type of bonus.
 */
void ptb::base_bonus::set_type(base_bonus_type t)
{
  m_type.clear();
  add_type(t);
  m_current_type = 0;
} // base_bonus::set_type()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a new type of bonus.
 * \param t The new type of bonus.
 */
void ptb::base_bonus::add_type(base_bonus_type t)
{
  if ( t != unknown_type )
    m_type.push_back(t);
} // base_bonus::add_type()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the stock.
 */
unsigned int ptb::base_bonus::get_stock() const
{
  return m_stock;
} // base_bonus::get_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the stock.
 * \param stock The new stock.
 */
void ptb::base_bonus::set_stock(unsigned int stock)
{
  m_stock = stock;
} // base_bonus::set_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set index of player that can take the bonus (0 if all players).
 * \param index The new player index.
 */
void ptb::base_bonus::set_player_index(unsigned int index)
{
  m_player_index = index;
} // base_bonus::set_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the player index to consider.
 */
unsigned int  ptb::base_bonus::get_player_index() const
{
  return m_player_index;
} // base_bonus::get_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the animation.
 */
const bear::visual::animation& ptb::base_bonus::get_animation() const
{
  return m_animation;
} // base_bonus::get_animation()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the animation.
 * \param anim the animation.
 */
void ptb::base_bonus::set_animation(const bear::visual::animation& anim)
{
  m_animation = anim;
} // base_bonus::set_animation()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a bonus type from its string representation.
 * \param t The string containing the type of the bonus.
 */
ptb::base_bonus::base_bonus_type
ptb::base_bonus::type_from_string( const std::string& t )
{
  if ( t == "air_power" ) return air_power;
  if ( t == "fire_power" ) return fire_power;
  if ( t == "water_power") return water_power;
  if ( t == "invincibility_power" ) return invincibility_power;
  if ( t == "stones_stock" ) return stones_stock;
  if ( t == "stones_big_stock" ) return stones_big_stock;
  if ( t == "one_more_life" ) return one_more_life;
  if ( t == "increase_max_energy" ) return increase_max_energy;
  if ( t == "switch_players" ) return switch_players;

  return unknown_type;
} // base_bonus::type_from_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a string containing the name of a bonus type.
 * \param t The bonus type.
 */
std::string ptb::base_bonus::type_to_string( base_bonus_type t )
{
  switch (t)
    {
    case air_power: return "air_power";
    case fire_power: return "fire_power";
    case water_power: return "water_power";
    case invincibility_power: return "invincibility_power";
    case stones_stock: return "stones_stock";
    case stones_big_stock: return "stones_big_stock";
    case one_more_life: return "one_more_life";
    case increase_max_energy: return "increase_max_energy";
    case switch_players: return "switch_players";
    case unknown_type: return "unknown_type";
    default: return "error: invalid type value";
    }
} // base_bonus::type_to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void ptb::base_bonus::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "\ntype: { ";

  for ( std::size_t i=0; i!=m_type.size(); ++i )
    oss << type_to_string(m_type[i]) << ' ';

  oss << "}\n stock: " << m_stock << "\n";
  str += oss.str();
} // base_bonus::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the bonus.
 * \param p The player.
 */
void ptb::base_bonus::give_bonus( const player_proxy& p )
{
  on_found(p.get_index());

  switch ( get_type() )
    {
    case air_power:
      game_variables::set_air_power(p.get_index(), true);
      break;
    case fire_power:
      game_variables::set_fire_power(p.get_index(), true);
      break;
    case water_power:
      game_variables::set_water_power(p.get_index(), true);
      break;
    case invincibility_power:
      p.set_invincible(true);
      break;
    case stones_stock:
    case stones_big_stock:
      game_variables::set_stones_count
        ( p.get_index(),
          game_variables::get_stones_count(p.get_index()) + m_stock);
      break;
    case  one_more_life:
      create_little_plee( p.get_rendering_attributes().is_mirrored() );
      break;
    case increase_max_energy:
      {
        give_max_energy(p);
        break;
      }
    case switch_players:
      {
        break;
      }
    case unknown_type:
      { CLAW_FAIL("base_bonus is of unknown type"); }
    }

  m_bonus_given = true;
  kill();
} // base_bonus::give_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the bonus.
 * \param plee_orientation The orientation of Plee.
 */
void ptb::base_bonus::create_little_plee( bool plee_orientation )
{
  little_plee* new_little_plee = new little_plee;

  new_item( *new_little_plee );

  CLAW_ASSERT(new_little_plee->is_valid(),
              "The little_plee isn't correctly initialized" );

  new_little_plee->set_center_of_mass(get_center_of_mass());
  new_little_plee->set_positive_orientation(plee_orientation);
  new_little_plee->set_z_position( get_z_position()+1 );
  new_little_plee->start();
} // base_bonus::create_little_plee()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do the actions related to a change in the bonus type.
 * \param t The new type of the bonus.
 */
void ptb::base_bonus::do_set_type(base_bonus_type t)
{
  // nothing to do
} // base_bonus::do_set_type()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give max energy bonus.
 */
void ptb::base_bonus::give_max_energy(const player_proxy& p)
{
  unsigned int energy =
    game_variables::get_max_energy(m_player_index) + m_stock;
  if ( energy > PTB_MAXIMUM_ENERGY )
    energy = PTB_MAXIMUM_ENERGY;

  game_variables::set_max_energy( m_player_index, energy );

  game_variables::set_current_level_max_energy_state(true);
  game_variables::set_current_level_max_energy_state(m_player_index, true);

  send_energy_notification(m_player_index);
} // base_bonus::give_max_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send a notification when max energy increase.
 */
void ptb::base_bonus::send_energy_notification(unsigned int index)
{
  status_layer_notification_message msg;

  bear::visual::sprite sp = 
    get_level_globals().auto_sprite
    ( "gfx/ui/bonus-icons/bonus-icons.png", "energy box" );
  msg.set_notification( index, sp, gettext("Energy bonus found"));

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // base_bonus::send_energy_notification()

