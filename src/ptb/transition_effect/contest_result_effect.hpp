/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An effect that displays a text "game over" and start the title
 *        screen.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_CONTEST_RESULT_EFFECT_HPP__
#define __PTB_CONTEST_RESULT_EFFECT_HPP__

#include "ptb/player_proxy.hpp"

#include "visual/writing.hpp"
#include "engine/transition_effect/fade_effect.hpp"

namespace ptb
{
  /**
   * \brief An effect that displays a text "game over" and start the title
   *        screen.
   * \author Sebastien Angibaud
   */
  class contest_result_effect:
    public bear::engine::fade_effect
  {
  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::fade_effect super;

  public:
    contest_result_effect();
    void build();
    bear::universe::time_type
    progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;

    void set_world( const bear::engine::world* w );
    void set_loser_index(unsigned int index);
    bool key_pressed( const bear::input::key_info& key );
    bool button_pressed
    ( bear::input::joystick::joy_code button, unsigned int joy_index );

  private:
    void update_bonus_state();

  private:
    /** \brief The sprite of player 1. */
    bear::visual::sprite m_player_1;

    /** \brief The sprite of player 2. */
    bear::visual::sprite m_player_2;

    /** \brief The world where we search for the bonus points. */
    const bear::engine::world* m_world;

    /** \brief The index of the loser. */
    unsigned int m_loser_index;
  }; // class contest_result_effect
} // namespace ptb

#endif // __PTB_CONTEST_RESULT_EFFECT_HPP__
