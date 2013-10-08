/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame is the menu to choose a level of the main story.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_FRAME_PLAY_STORY_HPP__
#define __PTB_FRAME_PLAY_STORY_HPP__

#include "ptb/frame/frame.hpp"
#include "ptb/gui/horizontal_gauge.hpp"
#include "gui/picture.hpp"
#include "gui/horizontal_flow.hpp"
#include "gui/scene_element.hpp"
#include "gui/static_text.hpp"
#include "engine/variable/var_map.hpp"

#include <vector>

namespace ptb
{
  class level_information;

  /**
   * \brief This frame is the menu to choose a level of the main story.
   * \author Sébastien Angibaud
   */
  class frame_play_story:
    public frame
  {
  private:
    /**
     * \brief A class that contains all visual component
     * to display player's informations.
     * \author Sébastien Angibaud
     */
    class player_status
    {
    public:
      /** \brief The visual component containing all informations.*/
      bear::gui::visual_component* component;

      /** \brief The text for score. */
      bear::gui::static_text* score_text;

      /** \brief The text for score. */
      bear::gui::static_text* lives_text;

      /** \brief Image of lives. */
      bear::gui::picture* lives_picture;

      /** \brief The text for stone number. */
      bear::gui::static_text* stone_text;

      /** \brief Image of stone. */
      bear::gui::picture* stone_picture;

      /** \brief Image of air power. */
      bear::gui::picture* air_power;

      /** \brief Image of air power. */
      bear::gui::picture* fire_power;

      /** \brief Image of air power. */
      bear::gui::picture* water_power;

      /** \brief Horizontal gauge for energy. */
      horizontal_gauge* energy;
    }; // player_status

    typedef frame super;

  public:
    frame_play_story( windows_layer* in_layer );
    void on_focus();

  private:
    void delete_levels();

    void create_controls();
    bear::gui::visual_component* create_ok_button();
    bear::gui::visual_component* create_back_button();
    bear::gui::visual_component* create_next_button();
    bear::gui::visual_component* create_previous_button();

    void create_bonus_component();
    void create_player_component(player_status& p);
    void position_controls( bear::gui::coordinate_type b );
    void player_status_position_controls( player_status& p );

    void update_controls();
    void update_bonus();
    void update_level_name();
    void update_all_players_status();
    void update_player_status(unsigned int index, player_status& p);
    void update_powers(unsigned int index, player_status& p);
    void update_power
    (bool power, const std::string& picture_name, bear::gui::picture* p);

    void load_and_sort_level_names();
    void sort_level_names
    (std::list<std::string>& level_names, bear::engine::var_map vars);

    void on_ok();
    bool on_close();
    void on_previous();
    void on_next();
    void on_bonus_selected(const std::string bonus_name);

    bear::visual::sprite get_thumb() const;
    bear::visual::sprite get_default_thumb() const;
    bear::visual::sprite get_status_picture() const;

  protected:
    void close_window() const;

  private:
    /* \brief The list of levels. */
    std::vector<level_information> m_levels;

    /* \brief The current mini-game. */
    unsigned int m_index;

    /** \brief The thumb of the level. */
    bear::gui::picture* m_thumb;

    /** \brief All components for first player status. */
    player_status m_first_player_status;

    /** \brief All component for second player status. */
    player_status m_second_player_status;

    /** \brief All component for bonus informations. */
    bear::gui::horizontal_flow* m_bonus;

    /** \brief The text for level's name. */
    bear::gui::scene_element* m_name_text;

    /** \brief The picture of the level's status. */
    bear::gui::picture* m_status_picture;

    /** \brief The text for bonus name. */
    //bear::gui::rectangle* m_bonus_rectangle;

    /** \brief The text for bonus name. */
    bear::gui::static_text* m_bonus_text;
  }; // class frame_play_story
} // namespace ptb

#endif // __PTB_FRAME_PLAY_STORY_HPP__
