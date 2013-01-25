/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The effect shown when the player is invincible.
 * \author Julien Jorge
 */
#ifndef __PTB_INVINCIBILITY_EFFECT_HPP__
#define __PTB_INVINCIBILITY_EFFECT_HPP__

#include "engine/transition_effect/fade_effect.hpp"

namespace ptb
{
  /**
   * \brief The effect shown when the player is invincible.
   * \author Julien Jorge
   */
  class invincibility_effect:
    public bear::engine::fade_effect
  {
  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::fade_effect super;

  public:
    invincibility_effect();
    invincibility_effect( const invincibility_effect& that );
    ~invincibility_effect();

    invincibility_effect& operator=( const invincibility_effect& that );

    void build();

    static bear::universe::time_type get_total_duration();

  private:
    /** \brief The identifier of the music played. */
    std::size_t m_music_id;

  }; // class invincibility_effect
} // namespace ptb

#endif // __PTB_INVINCIBILITY_EFFECT_HPP__
