/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::item_waiting_for_players class.
 * \author Julien Jorge
 */

#include "ptb/game_variables.hpp"

#include <limits>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
template<class Base>
ptb::item_waiting_for_players<Base>::item_waiting_for_players()
  : m_current_animation(&m_off)
{

} // item_waiting_for_players::item_waiting_for_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Copy constructor.
 * \param that The instance to copy from.
 */
template<class Base>
ptb::item_waiting_for_players<Base>::item_waiting_for_players
( const item_waiting_for_players<Base>& that)
  : m_off(that.m_off), m_single_one(that.m_single_one),
    m_single_two(that.m_single_two), m_all(that.m_all),
    m_current_animation(&m_off)
{

} // item_waiting_for_players::item_waiting_for_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if ( m_current_animation->is_valid() )
    m_current_animation->next(elapsed_time);

  bool check_first_player = check_action(m_first_player);
  bool check_second_player = check_action(m_second_player);
  const bool change = (m_previous_check_second_player != check_second_player)
    || (m_previous_check_first_player != check_first_player);

  if ( (m_first_player != NULL) && check_first_player )
    {
      if (game_variables::get_players_count()==2)
        {
          if ( (m_second_player != NULL) && check_second_player )
            {
              if ( change )
                all_players(m_first_player, m_second_player);

              progress_all_players
                (elapsed_time, m_first_player, m_second_player);
            }
          else
            {
              if ( change )
                one_player(m_first_player);

              progress_one_player(elapsed_time, m_first_player);
            }
        }
      else
        {
          if ( change )
            all_players(m_first_player, player_proxy());

          progress_all_players(elapsed_time, m_first_player, player_proxy());
        }
    }
  else if ( (m_second_player != NULL) && check_second_player )
    {
      if ( change )
        one_player(m_second_player);

      progress_one_player(elapsed_time, m_second_player);
    }
  else
    {
      if ( change )
        no_player();

      progress_no_player(elapsed_time);
    }

  m_previous_check_first_player = check_first_player;
  m_previous_check_second_player = check_second_player;

  m_first_player = player_proxy();
  m_second_player = player_proxy();
} // item_waiting_for_players::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::build()
{
  super::build();

  m_current_animation = &m_off;
} // item_waiting_for_players::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  super::get_visual( visuals );

  super::add_visual( *m_current_animation, visuals );
} // item_waiting_for_players::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type visual::animation.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 *
 * Valid values for the \a name and \a value parameters are :
 *  - "animation", visual::animation
 *  - anything supported by the parent class
 */
template<class Base>
bool ptb::item_waiting_for_players<Base>::set_animation_field
( const std::string& name, const bear::visual::animation& value )
{
  bool ok = true;

  if (name == "item_waiting_for_players.animation_for_all")
    m_all = value;
  else  if (name == "item_waiting_for_players.animation_for_single_one")
    m_single_one = value;
  else  if (name == "item_waiting_for_players.animation_for_single_two")
    m_single_two = value;
  else  if (name == "item_waiting_for_players.animation_off")
    m_off = value;
  else
    ok = super::set_animation_field(name, value);

  return ok;
} // item_waiting_for_players::set_animation_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of <std::string>.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
template<class Base>
bool ptb::item_waiting_for_players<Base>::set_string_list_field
( const std::string& name, const std::vector<std::string>& value )
{
  bool result = false;

  if ( name == "item_waiting_for_players.allowed_actions" )
    {
      for (std::size_t i=0; i!=value.size(); ++i)
        m_allowed_actions.insert(value[i]);

      result = true;
    }
  else
    result = super::set_string_list_field( name, value );

  return result;
} // players_present::set_string_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if all players are present.
 */
template<class Base>
bool ptb::item_waiting_for_players<Base>::all_players_present() const
{
  return m_current_animation == &m_all;
} // item_waiting_for_players::all_players_present()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if one player is present.
 */
template<class Base>
bool ptb::item_waiting_for_players<Base>::one_player_present() const
{
  return ( m_current_animation == &m_single_one )
    || ( m_current_animation == &m_single_two );
} // item_waiting_for_players::one_player_present()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called in a two players game, when only one player is colliding
 *        with the item.
 * \param p The player colliding with the item.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::one_player( const player_proxy& p )
{
  if ( p.get_index() == 1 )
    m_current_animation = &m_single_one;
  else
    m_current_animation = &m_single_two;

  m_current_animation->reset();

  on_one_player(p);
} // item_waiting_for_players::one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when all players are colliding with the item.
 * \param p1 The first player, colliding with the item.
 * \param p2 The second player, colliding with the item. In single player games,
 *        (p2 == NULL) is verified.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::all_players
( const player_proxy& p1, const player_proxy& p2 )
{
  m_current_animation = &m_all;
  m_current_animation->reset();

  on_all_players(p1, p2);
} // item_waiting_for_players::all_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called in a two players game, when there is no player around.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::no_player()
{
  m_current_animation = &m_off;
  m_current_animation->reset();

  on_no_player();
} // item_waiting_for_players::no_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item in a two players game, when
 *        only one player is colliding with the item.
 * \param elapsed_time Elapsed time since the last call.
 * \param p The player colliding with the item.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::progress_one_player
( bear::universe::time_type elapsed_time, const player_proxy& p )
{
  do_progress_one_player(elapsed_time, p);
} // item_waiting_for_players::progress_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item, when all players are
 *        colliding with the item.
 * \param elapsed_time Elapsed time since the last call.
 * \param p1 The first player, colliding with the item.
 * \param p2 The second player, colliding with the item. In single player games,
 *        this pointer is NULL.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::progress_all_players
( bear::universe::time_type elapsed_time, const player_proxy& p1,
  const player_proxy& p2 )
{
  do_progress_all_players
    (elapsed_time, p1, p2);
} // item_waiting_for_players::progress_all_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item, when there is no player
 *        around.
 * \param elapsed_time Elapsed time since the last call.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::progress_no_player
( bear::universe::time_type elapsed_time )
{
  do_progress_no_player(elapsed_time);
} // item_waiting_for_players::progress_no_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called in a two players game, when only one player is colliding
 *        with the item.
 * \param p The player colliding with the item.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::on_one_player( const player_proxy& p )
{
  // do nothing
} // item_waiting_for_players::on_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when all players are colliding with the item.
 * \param p1 The first player, colliding with the item.
 * \param p2 The second player, colliding with the item. In single player games,
 *        this pointer is NULL.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::on_all_players
( const player_proxy& p1, const player_proxy& p2 )
{
  // do nothing
} // item_waiting_for_players::on_all_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called in a two players game, when there is no player around.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::on_no_player()
{
  // do nothing
} // item_waiting_for_players::on_no_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item in a two players game, when
 *        only one player is colliding with the item.
 * \param elapsed_time Elapsed time since the last call.
 * \param p The player colliding with the item.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::do_progress_one_player
( bear::universe::time_type elapsed_time, const player_proxy& p )
{
  // do nothing
} // item_waiting_for_players::do_progress_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item, when all players are
 *        colliding with the item.
 * \param elapsed_time Elapsed time since the last call.
 * \param p1 The first player, colliding with the item.
 * \param p2 The second player, colliding with the item. In single player games,
 *        this pointer is NULL.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::do_progress_all_players
( bear::universe::time_type elapsed_time, const player_proxy& p1,
  const player_proxy& p2 )
{
  // do nothing
} // item_waiting_for_players::do_progress_all_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item, when there is no player
 *        around.
 * \param elapsed_time Elapsed time since the last call.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::do_progress_no_player
( bear::universe::time_type elapsed_time )
{
  // do nothing
} // item_waiting_for_players::do_progress_no_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if a given player satisfies action restriction
 * \param p The player.
 */
template<class Base>
bool ptb::item_waiting_for_players<Base>::check_action( const player_proxy& p )
{
  bool result(false);

  if ( p.get_player_instance() != NULL )
    {
      if ( m_allowed_actions.empty() )
        result = true;
      else
        {
          std::set<std::string>::const_iterator it;
          it = m_allowed_actions.find(p.get_current_action_name());
          result = ( it != m_allowed_actions.end());
        }
    }

  return result;
} // item_waiting_for_players::check_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Collision with an other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
template<class Base>
void ptb::item_waiting_for_players<Base>::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    {
      if ( p.get_index() == 1 )
        m_first_player = p;
      else
        m_second_player = p;
    }
} // item_waiting_for_players::collision()
