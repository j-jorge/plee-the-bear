/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::power_filter_door class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/power_filter_door.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/player_proxy.hpp"
#include "ptb/item/stone/stone.hpp"
#include "ptb/item/small_honeypot.hpp"
#include "ptb/item/power_drop_restriction_zone.hpp"
#include "generic_items/decorative_item.hpp"

BASE_ITEM_EXPORT( power_filter_door, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::power_filter_door::power_filter_door()
  : m_door_type(unknown_type),
    m_first_player_status(not_here), m_second_player_status(not_here),
    m_remove_power(true)
{
  set_phantom(false);
  set_can_move_items(true);
} // power_filter_door::power_filter_door()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::power_filter_door::pre_cache()
{
  get_level_globals().load_animation("animation/power-filter-door/air.canim");
  get_level_globals().load_animation("animation/power-filter-door/fire.canim");
  get_level_globals().load_animation
    ("animation/power-filter-door/water.canim");
  get_level_globals().load_animation
    ("animation/power-filter-door/waves.canim");
    get_level_globals().load_animation
    ("animation/power-filter-door/back-waves.canim");
} // power_filter_door::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::power_filter_door::build()
{
  switch(m_door_type)
    {
    case fire_door:
      set_animation
        ( get_level_globals().get_animation
          ("animation/power-filter-door/fire.canim") );
      break;
    case air_door:
      set_animation
        ( get_level_globals().get_animation
          ("animation/power-filter-door/air.canim") );
      break;
    case water_door:
      set_animation
        ( get_level_globals().get_animation
          ("animation/power-filter-door/water.canim") );
      break;
    default:
      {
        CLAW_ASSERT( false, "'unknown_type' is not a valid power." );
      }
    }

  create_power_restriction_zone();
} // power_filter_door::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::power_filter_door::progress( bear::universe::time_type elapsed_time )
{
  update_player_status(1, m_first_player_status, m_first_player_position);
  update_player_status(2, m_second_player_status, m_second_player_position);
} // power_filter_door::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::power_filter_door::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "power_filter_door.type" )
    {
      if ( value == "air_door" )
        m_door_type = air_door;
      else if ( value == "fire_door" )
        m_door_type = fire_door;
      else if ( value == "water_door" )
        m_door_type = water_door;
    }
  else
    result = super::set_string_field( name, value );

  return result;
} // power_filter_door::set_string_field()


/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "bool".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::power_filter_door::set_bool_field
( const std::string& name, bool value )
{
  bool result = true;

  if ( name == "power_filter_door.remove_power" )
    m_remove_power = value;
  else
    result = super::set_bool_field( name, value );

  return result;
} // power_filter_door::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player or a stone.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::power_filter_door::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    {
      if ( p.get_index() == 1 )
        apply_collision_player
          (that, info, p, m_first_player_status, m_first_player_position);
      else
        apply_collision_player
          (that, info, p, m_second_player_status, m_second_player_position);
    }
  else
    {
      stone* s = dynamic_cast<stone*>(&that);

      if ( s != NULL  )
        apply_collision_stone(that, info, s);
      else
        default_collision(info);
    }
} // power_filter_door::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::power_filter_door::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // power_filter_door::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration.
 * \param info Some informations about the collision.
 * \param push_up Indicates if the decoration is a push_up.
 */
void ptb::power_filter_door::create_decoration
( bear::universe::collision_info& info, bool push_up)
{
  bear::decorative_item* item = new bear::decorative_item;

  if ( push_up )
    item->set_animation
      (get_level_globals().get_animation
       ("animation/power-filter-door/waves.canim"));
  else
    item->set_animation
      (get_level_globals().get_animation
       ("animation/power-filter-door/back-waves.canim"));

  item->auto_size();
  item->get_rendering_attributes().set_angle(get_visual_angle());
  item->set_kill_when_finished(true);
  item->set_z_position(get_z_position()-1);
  item->set_center_of_mass(get_center_of_mass());

  if ( info.get_collision_side() == bear::universe::zone::middle_left_zone )
    {
      item->set_right(get_left());
      item->get_rendering_attributes().mirror(true);
    }
  else
    item->set_left(get_right());

  CLAW_ASSERT
    ( item->is_valid(),
      "The decoration of power_filter_door isn't correctly initialized" );

  new_item( *item );
} // power_filter_door::create_decoration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the stone has the good power.
 */
bool ptb::power_filter_door::check_power_of_stone( stone* s ) const
{
  bool result = false;

  if ( m_door_type == air_door )
    result = s->has_air_power();
  else if ( m_door_type == fire_door )
    result = s->has_fire_power();
  else if ( m_door_type == water_door )
    result = s->has_water_power();

  return result;
} // power_filter_door::check_power_of_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the player has the good power.
 * \param index The index of the player to check.
 */
bool ptb::power_filter_door::check_power_of_player( unsigned int index ) const
{
  bool result = false;

  if ( m_door_type == air_door )
    result = game_variables::get_air_power(index);
  else if ( m_door_type == fire_door )
    result = game_variables::get_fire_power(index);
  else if ( m_door_type == water_door )
    result = game_variables::get_water_power(index);

  return result;
} // power_filter_door::check_power_of_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the status of a player and create a honeypot if a player left
 *        the door.
 * \param index the index of the considered player.
 * \param status The status of the player (in/out).
 * \param pos The last position of the player (in/out).
 */
void ptb::power_filter_door::update_player_status
(unsigned int index, player_status& status, bear::universe::position_type& pos)
{
  if ( status == want_move_right )
    status = move_right;
  else  if ( status == want_move_left )
    status = move_left;
  else
    {
      if ( m_remove_power &&
           ( status == move_right ) && ( pos.x > get_left() ) )
        {
          create_small_honeypot(status, pos);

          if ( m_door_type == air_door )
            game_variables::set_air_power(index, false);
          else if ( m_door_type == fire_door )
            game_variables::set_fire_power(index, false);
          else
            game_variables::set_water_power(index, false);
        }
      else if ( m_remove_power &&
                ( status == move_left ) && ( pos.x < get_right() ) )
        {
          create_small_honeypot(status, pos);

          if ( m_door_type == air_door )
            game_variables::set_air_power(index, false);
          else if ( m_door_type == fire_door )
            game_variables::set_fire_power(index, false);
          else
            game_variables::set_water_power(index, false);
        }

      status = not_here;
    }
} // power_filter_door::update_player_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the collision with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 * \param p The the player.
 * \param status The status of the player (in/out).
 * \param pos The last position of the player (in/out).
 */
void ptb::power_filter_door::apply_collision_player
( bear::engine::base_item& that, bear::universe::collision_info& info,
  const player_proxy& p, player_status& status,
  bear::universe::position_type& pos)
{
  pos = p.get_center_of_mass();
  const bool ok(check_power_of_player(p.get_index()));

  if ( (info.get_collision_side() == bear::universe::zone::middle_left_zone) ||
       (info.get_collision_side() == bear::universe::zone::middle_right_zone) )
    {
      if ( ok )
        {
          create_decoration(info, false);
          if ( ( info.get_collision_side() ==
                 bear::universe::zone::middle_left_zone ) )
            status = want_move_right;
          else
            status = want_move_left;
        }
      else
        {
          create_decoration(info, true);
          default_collision(info);
          status = not_here;

          if ( ( info.get_collision_side() ==
                 bear::universe::zone::middle_left_zone ) )
            that.add_external_force
              (bear::universe::force_type(that.get_mass() * -30000, 0));
          else
            that.add_external_force
              (bear::universe::force_type(that.get_mass() * 30000, 0));
        }
    }
  else
    {
      if ( status == move_right )
        status =  want_move_right;
      else if ( status == move_left )
        status =  want_move_left;

      default_collision(info);
    }
} // power_filter_door::apply_collision_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the collision with a stone.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 * \param s The pointer on the stone.
 */
void ptb::power_filter_door::apply_collision_stone
( bear::engine::base_item& that, bear::universe::collision_info& info,
  stone* s )
{
  if ( !check_power_of_stone(s) )
    {
      create_decoration(info, true);
      default_collision(info);

      if ( info.get_collision_side() ==
           bear::universe::zone::middle_left_zone  )
        that.add_external_force
          (bear::universe::force_type(that.get_mass() * -30000, 0));
      else
        that.add_external_force
          (bear::universe::force_type(that.get_mass() * 30000, 0));
    }
  else if ( ( info.get_collision_side() ==
              bear::universe::zone::middle_left_zone ) ||
            ( info.get_collision_side() ==
              bear::universe::zone::middle_right_zone ) )
    create_decoration(info, false);
} // power_filter_door::apply_collision_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a honeypot.
 * \param status The state in which the player collides with this.
 * \param pos The position where the pot is created.
 */
void ptb::power_filter_door::create_small_honeypot
(player_status status, const bear::universe::position_type& pos)
{
  small_honeypot* new_small_honeypot = new small_honeypot();

  new_small_honeypot->set_z_position(get_z_position() + 1);

  new_small_honeypot->set_center_of_mass(pos);
  if ( m_door_type == air_door )
    new_small_honeypot->set_type(base_bonus::air_power);
  else if ( m_door_type == fire_door )
    new_small_honeypot->set_type(base_bonus::fire_power);
  else
    new_small_honeypot->set_type(base_bonus::water_power);

  CLAW_ASSERT
    ( new_small_honeypot->is_valid(),
      "The small_honeypot of power_filter_door isn't correctly initialized" );

  new_item( *new_small_honeypot );

  if ( status == move_right )
    {
      new_small_honeypot->set_right(get_left());
      new_small_honeypot->add_external_force
        (bear::universe::force_type(-30000, 0));
    }
  else
    {
      new_small_honeypot->set_left(get_right());
      new_small_honeypot->add_external_force
        (bear::universe::force_type(30000, 0));
    }
} // ptb::power_filter_door::create_small_honeypot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the zone in which a player cannot throw a power.
 */
void ptb::power_filter_door::create_power_restriction_zone()
{
  power_drop_restriction_zone* item = new power_drop_restriction_zone();

  item->set_width(get_width()+120);
  item->set_height(get_height());
  item->set_center_of_mass(get_center_of_mass());

  if ( m_door_type == air_door )
    item->set_powers_restriction(true, false, false);
  else if ( m_door_type == fire_door )
    item->set_powers_restriction(false, true, false);
  else
    item->set_powers_restriction(false, false, true);

  CLAW_ASSERT
    ( item->is_valid(),
      "The power_drop_restriction_zone isn't correctly initialized" );

  new_item( *item );
} // ptb::power_filter_door::create_power_restriction_zone()
