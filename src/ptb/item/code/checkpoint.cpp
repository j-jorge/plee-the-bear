/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::checkpoint class.
 * \author Julien Jorge
 */
#include "ptb/item/checkpoint.hpp"

#include "engine/export.hpp"

BASE_ITEM_EXPORT( checkpoint, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::checkpoint::checkpoint()
  : sniffable("checkpoint")
{
  set_size(35, 120);
  can_be_reactivated(true);
} // checkpoint::checkpoint()

/*----------------------------------------------------------------------------*/
/**
 * \brief Pre-cache the datas used by the item.
 */
void ptb::checkpoint::pre_cache()
{
  get_level_globals().load_sound("sound/checkpoint-ding.ogg");
  get_level_globals().load_sound("sound/checkpoint-slide.ogg");
} // checkpoint::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::checkpoint::build()
{
  if (get_player_index() == 1)
    {
      m_animation =
        get_level_globals().get_animation("animation/checkpoint-1.canim");

      checkpoint* right_part = new checkpoint(*this);
      right_part->set_left(get_right());
      right_part->set_player_index(2);
      right_part->m_animation =
        get_level_globals().get_animation("animation/checkpoint-2.canim");

      if ( get_insert_as_static() )
        right_part->set_insert_as_static();

      new_item( *right_part );

      // specific to the left part
      set_gap_x(-15);
    }
} // checkpoint::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::checkpoint::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if (is_activated())
    m_animation.next(elapsed_time);
} // checkpoint::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprites of the item.
 * \param visuals (out) The visuals of the item.
 */
void ptb::checkpoint::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  add_visual(m_animation, visuals);
} // checkpoint::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Play the sounds of the activation.
 */
void ptb::checkpoint::activate()
{
  bear::audio::sound_effect e;
  e.set_position(get_center_of_mass());

  get_level_globals().play_sound("sound/checkpoint-ding.ogg", e);
  get_level_globals().play_sound("sound/checkpoint-slide.ogg", e);

  on_found(get_player_index());
} // checkpoint::activate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Play the sounds of the reactivation.
 */
void ptb::checkpoint::reactivate()
{
  bear::audio::sound_effect e;
  e.set_position(get_center_of_mass());

  get_level_globals().play_sound("sound/checkpoint-ding.ogg", e);

  on_found(get_player_index());
} // checkpoint::reactivate()
