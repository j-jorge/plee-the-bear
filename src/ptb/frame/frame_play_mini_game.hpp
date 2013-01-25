/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This frame is the main menu of mini-games.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_FRAME_PLAY_MINI_GAME_HPP__
#define __PTB_FRAME_PLAY_MINI_GAME_HPP__

#include "ptb/frame/frame.hpp"
#include "gui/picture.hpp"
#include "gui/scene_element.hpp"
#include "gui/static_text.hpp"

#include <vector>

namespace ptb
{
  class mini_game_information;

  /**
   * \brief This frame is the main menu of mini-games.
   * \author Sébastien Angibaud
   */
  class frame_play_mini_game:
    public frame
  {
    typedef frame super;

  public:
    frame_play_mini_game
    ( windows_layer* in_layer, const std::string& filename );
    void on_focus();

  private:
    void delete_mini_games();

    void create_controls();
    bear::gui::visual_component* create_ok_button();
    bear::gui::visual_component* create_back_button();
    bear::gui::visual_component* create_next_button();
    bear::gui::visual_component* create_previous_button();

    void create_text();
    void position_controls( bear::gui::coordinate_type b );
    void update_controls();
    void update_mini_game_state();
    void load_levels( const std::string& filename );

    void on_ok();
    bool on_close();
    void on_previous();
    void on_next();

    bear::visual::sprite get_thumb() const;
    bear::visual::sprite get_default_thumb() const;
    bear::visual::sprite get_status_picture() const;

  private:
    /* \brief The list of mini-games. */
    std::vector<mini_game_information> m_levels;

    /* \brief The current mini-game. */
    unsigned int m_index;

    /** \brief The thumb of the minigame. */
    bear::gui::picture* m_thumb;

    /** \brief The text for mini-game's name. */
    bear::gui::scene_element* m_name_text;

    /** \brief The text for mini-game's informations. */
    bear::gui::static_text* m_informations;

    /** \brief The text for record informations. */
    bear::gui::static_text* m_records;

    /** \brief The picture of the mini-game's status. */
    bear::gui::picture* m_status_picture;

  }; // class frame_play_mini_game
} // namespace ptb

#endif // __PTB_FRAME_PLAY_MINI_GAME_HPP__
