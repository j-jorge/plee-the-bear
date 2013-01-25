/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::game_over_effect class.
 * \author Julien Jorge
 */
#include "ptb/transition_effect/game_over_effect.hpp"
#include "ptb/item/bonus_points/bonus_points.hpp"
#include "ptb/item/bonus_manager.hpp"

#include "engine/game.hpp"
#include "engine/level.hpp"
#include "engine/world.hpp"
#include "visual/scene_writing.hpp"

#include "ptb/util/player_util.hpp"

#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::game_over_effect::game_over_effect()
  : m_world(NULL)
{

} // game_over_effect::game_over_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the effect.
 */
void ptb::game_over_effect::build()
{
  super::build();
  set_color(0, 0, 0);
  set_duration(1, 10, 0);

  bear::visual::font fnt
    ( get_level_globals().get_font("font/level_name-42x50.fnt", 50) );
  m_game_over.create(fnt, gettext("game over"));

  m_first_player = util::find_player( get_level_globals(), 1 );
  m_second_player = util::find_player( get_level_globals(), 2 );

  get_level_globals().stop_all_musics();
  get_level_globals().play_music("music/game-over.ogg", 1);

  update_bonus_state();
} // game_over_effect::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the components of the effect.
 * \param elapsed_time Elapsed time since the last call.
 */
bear::universe::time_type
ptb::game_over_effect::progress( bear::universe::time_type elapsed_time )
{
  const bear::universe::time_type result( super::progress(elapsed_time) );

  if ( is_finished() )
    bear::engine::game::get_instance().set_waiting_level
      ("level/title_screen.cl");

  return result;
} // game_over_effect::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the components of the effect.
 * \param e (out) The scene elements.
 */
void ptb::game_over_effect::render( scene_element_list& e ) const
{
  super::render(e);

  e.push_back
    ( bear::visual::scene_writing
      ( (get_layer().get_size().x - m_game_over.get_width()) / 2,
        m_game_over.get_height(),
        m_game_over ) );

  std::list<bear::engine::scene_visual> tmp;

  if ( m_first_player != NULL )
    m_first_player.get_visual(tmp);
  if ( m_second_player != NULL )
    m_second_player.get_visual(tmp);

  tmp.sort( bear::engine::scene_visual::z_position_compare() );

  for ( ; !tmp.empty(); tmp.pop_front() )
    e.push_back
      ( get_level().element_to_screen_coordinates(tmp.front().scene_element) );
} // game_over_effect::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the world in which we search the bonus points.
 * \param w The world.
 */
void ptb::game_over_effect::set_world( const bear::engine::world* w )
{
  m_world = w;
} // game_over_effect::set_world()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a key had been pressed.
 * \param key The value of the pressed key.
 * \remark This effect pretends to treat all keys, so we can maintain the pause
 *         mode.
 */
bool ptb::game_over_effect::key_pressed( const bear::input::key_info& key )
{
  // prevent pausing the game
  return true;
} // game_over_effect::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a joystick button had been pressed.
 * \param button The value of the pressed button.
 * \param joy_index The index of the joystick.
 * \remark This effect pretends to treat all keys, so we can maintain the pause
 *         mode.
 */
bool ptb::game_over_effect::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  // prevent pausing the game
  return true;
} // game_over_effect::button_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update bonus states alive in the world.
 */
void ptb::game_over_effect::update_bonus_state()
{
  if ( m_world == NULL )
    return;

  bear::engine::world::const_item_iterator it;

  for (it=m_world->living_items_begin(); it!=m_world->living_items_end(); ++it)
    {
      bonus_manager* manager =
        dynamic_cast<bonus_manager*>(&(*it));

      if ( manager != NULL )
        manager->manage(false);
    }
} // game_over_effect::update_bonus_state()
