/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::shared_camera class.
 * \author Julien Jorge
 */
#include "ptb/item/shared_camera.hpp"

#include "ptb/util/player_util.hpp"

BASE_ITEM_EXPORT( shared_camera, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param mode The mode to se the camera to.
 */
ptb::shared_camera::set_placement_message::set_placement_message
( placement_mode mode )
  : m_mode(mode)
{

} // set_placement_message::set_placement_message()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the message to a camera.
 * \param that The camera to apply the message to.
 */
bool ptb::shared_camera::set_placement_message::apply_to( shared_camera& that )
{
  that.set_mode( m_mode );
  return true;
} // set_placement_message::apply_to()




/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::shared_camera::shared_camera()
  : m_placement(shared), m_progress(&shared_camera::progress_no_players)
{
  set_active_on_build();
} // shared_camera::shared_camera()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::shared_camera::build()
{
  super::build();
} // shared_camera::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::shared_camera::progress( bear::universe::time_type elapsed_time )
{
  (this->*m_progress)(elapsed_time);
} // shared_camera::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the placement mode.
 * \param mode The new mode.
 */
void ptb::shared_camera::set_mode( placement_mode mode )
{
  if ( mode == lock_first_player )
    {
      if ( m_placement == lock_first_player )
        m_placement = shared;
      else
        m_placement = mode;
    }
  else if ( mode == lock_second_player )
    {
      if ( m_placement == lock_second_player )
        m_placement = shared;
      else
        m_placement = mode;
    }
  else
    m_placement = mode;
} // shared_camera::set_mode()

/*----------------------------------------------------------------------------*/
/**
 * \brief Compute the position of the camera.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::shared_camera::auto_position
( bear::universe::time_type elapsed_time )
{
  switch(m_placement)
    {
    case lock_first_player: set_first_player(elapsed_time); break;
    case lock_second_player: set_second_player(elapsed_time); break;
    case shared: set_shared(elapsed_time); break;
    case do_nothing: break;
    }
} // shared_camera::auto_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Center the camera on the first player.
 * \param elapsed_time Elapsed time since the last call.
 */
void
ptb::shared_camera::set_first_player( bear::universe::time_type elapsed_time )
{
  if ( m_first_player != NULL )
    adjust_position( m_first_player.hot_spot(), elapsed_time );
  else if ( m_second_player != NULL )
    set_second_player( elapsed_time );
  else
    m_placement = do_nothing;
} // shared_camera::set_first_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Center the camera on the second player.
 * \param elapsed_time Elapsed time since the last call.
 */
void
ptb::shared_camera::set_second_player( bear::universe::time_type elapsed_time )
{
  if ( m_second_player != NULL )
    adjust_position( m_second_player.hot_spot(), elapsed_time );
  else if ( m_first_player != NULL )
    set_first_player( elapsed_time );
  else
    m_placement = do_nothing;
} // shared_camera::set_second_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Center the camera between the two players.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::shared_camera::set_shared( bear::universe::time_type elapsed_time )
{
  if ( m_first_player != NULL )
    {
      if ( m_second_player != NULL )
        {
          bear::universe::position_type center1;
          bear::universe::position_type center2;

          center1 = m_first_player.hot_spot();
          center2 = m_second_player.hot_spot();

          adjust_position( (center1 + center2) / 2, elapsed_time );
        }
      else
        set_first_player( elapsed_time );
    }
  else if ( m_second_player != NULL )
    set_second_player( elapsed_time );
  else
    m_placement = do_nothing;
} // shared_camera::set_shared()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search players.
 */
void ptb::shared_camera::search_players()
{
  if ( m_first_player == NULL )
    m_first_player = util::find_player( get_level_globals(), 1 );

  if ( m_second_player == NULL )
    m_second_player = util::find_player( get_level_globals(), 2 );
} // shared_camera::search_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search the players and update the position of the camera.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::shared_camera::progress_no_players
( bear::universe::time_type elapsed_time )
{
  search_players();

  if ( m_first_player!=NULL )
    {
      m_progress = &shared_camera::progress_with_players;

      if ( m_second_player!=NULL )
        teleport
          ( (m_first_player.hot_spot() + m_second_player.hot_spot()) / 2 );
      else
        teleport( m_first_player.hot_spot() );
    }
  else if ( m_second_player!=NULL )
    {
      m_progress = &shared_camera::progress_with_players;
      teleport( m_second_player.hot_spot() );
    }
  else
    progress_zoom(elapsed_time);
} // shared_camera::progress_no_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the position of the camera.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::shared_camera::progress_with_players
( bear::universe::time_type elapsed_time )
{
  progress_zoom(elapsed_time);
  auto_position(elapsed_time);
} // shared_camera::progress_with_players()
