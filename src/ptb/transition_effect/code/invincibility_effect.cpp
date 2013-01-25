/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::invincibility_effect class.
 * \author Julien Jorge
 */
#include "ptb/transition_effect/invincibility_effect.hpp"

#include "engine/level_globals.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::invincibility_effect::invincibility_effect()
  : m_music_id(0)
{

} // invincibility_effect::invincibility_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Copy constructor.
 * \param that The instance to copy from.
 */
ptb::invincibility_effect::invincibility_effect
( const invincibility_effect& that )
  : fade_effect(that), m_music_id(0)
{

} // invincibility_effect::invincibility_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::invincibility_effect::~invincibility_effect()
{
  if (m_music_id!=0)
    get_level_globals().stop_music(m_music_id);
} // invincibility_effect::~invincibility_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Assignment.
 * \param that The instance to copy from.
 */
ptb::invincibility_effect&
ptb::invincibility_effect::operator=( const invincibility_effect& that )
{
  super::operator=(that);
  return *this;
} // invincibility_effect::operator=()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the effect.
 */
void ptb::invincibility_effect::build()
{
  super::build();
  set_color(1, 0.5, 0);
  set_opacity(0.25);
  set_duration(1, get_total_duration() - 2, 1);

  m_music_id = get_level_globals().play_music("music/invincibility.ogg", 1);
} // invincibility_effect::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the default duration of the invincibility.
 * \remark The duration must match the duration of the music.
 */
bear::universe::time_type ptb::invincibility_effect::get_total_duration()
{
  return 20; // 20 seconds
} // invincibility_effect::get_total_duration()
