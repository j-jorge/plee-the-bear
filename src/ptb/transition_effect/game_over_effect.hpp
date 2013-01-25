/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An effect that displays a text "game over" and start the title
 *        screen.
 * \author Julien Jorge
 */
#ifndef __PTB_GAME_OVER_EFFECT_HPP__
#define __PTB_GAME_OVER_EFFECT_HPP__

#include "ptb/player_proxy.hpp"

#include "visual/writing.hpp"
#include "engine/transition_effect/fade_effect.hpp"

namespace ptb
{
  /**
   * \brief An effect that displays a text "game over" and start the title
   *        screen.
   * \author Julien Jorge
   */
  class game_over_effect:
    public bear::engine::fade_effect
  {
  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::fade_effect super;

  public:
    game_over_effect();
    void build();
    bear::universe::time_type
    progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;

    void set_world( const bear::engine::world* w );
    bool key_pressed( const bear::input::key_info& key );
    bool button_pressed
    ( bear::input::joystick::joy_code button, unsigned int joy_index );

  private:
    void update_bonus_state();

  private:
    /** \brief The text. */
    bear::visual::writing m_game_over;

    /** \brief Pointer on the first player. */
    player_proxy m_first_player;

    /** \brief Pointer on the second player. */
    player_proxy m_second_player;

    /** \brief The world where we search for the bonus points. */
    const bear::engine::world* m_world;
  }; // class game_over_effect
} // namespace ptb

#endif // __PTB_GAME_OVER_EFFECT_HPP__
