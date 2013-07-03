/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that unlocks a mini-game.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_MINI_GAME_UNLOCK_ITEM_HPP__
#define __PTB_MINI_GAME_UNLOCK_ITEM_HPP__

#include "ptb/item/notification_toggle.hpp"

#include "engine/export.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/with_text.hpp"
#include "engine/scene_visual.hpp"

namespace ptb
{
  /**
   * \brief A item that unlocks a mini-game.
   *
   * The valid fields for this item are
   *  - \a minigame_name: (string) the name of the minigame,
   *  - \a unlocked_sentence: (string) the sentence displayed when the minigame
   *    is unlocked,
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class mini_game_unlock_item:
    public bear::engine::basic_renderable_item< ptb::notification_toggle >,
    public bear::engine::with_text
  {
    DECLARE_BASE_ITEM(mini_game_unlock_item);

  public:
    typedef bear::engine::basic_renderable_item
    < ptb::notification_toggle > super;

  public:
    bool is_valid() const;
    bool set_string_field( const std::string& name, const std::string& value );

    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;

  protected:
    void on_toggle_on(base_item* activator);

  private:
    void create_text_decoration();

  private:
    /** \brief The name of the mini-game. */
    std::string m_mini_game_name;

    /** \brief The sentence that is written when the mini-game is unlocked. */
    std::string m_unlocked_sentence;
  }; // class mini_game_unlock_item
} // namespace ptb

#endif // __PTB_MINI_GAME_UNLOCK_ITEM_HPP__
