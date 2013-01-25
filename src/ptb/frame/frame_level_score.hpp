/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This frame asks for the player's name to save the records.
 * \author Julien Jorge.
 */
#ifndef __PTB_FRAME_LEVEL_SCORE_HPP__
#define __PTB_FRAME_LEVEL_SCORE_HPP__

#include "ptb/frame/frame.hpp"
#include "gui/text_input.hpp"

namespace ptb
{
  class score_table;

  /**
   * \brief This frame asks for the player's name to save the records.
   * \author Julien Jorge.
   */
  class frame_level_score:
    public frame
  {
  public:
    frame_level_score
    ( windows_layer* in_layer, score_table& t, double score,
      const std::string& medal, const std::string& format,
      const std::string& next_level );

  private:
    void create_controls( const std::string& medal, const std::string& format );
    void create_new_record_controls
    ( const std::string& medal, const std::string& format );
    void create_no_new_record_controls
    ( const std::string& medal, const std::string& format );
    bear::gui::visual_component* create_input();
    bear::gui::visual_component* create_discard_button();
    bear::gui::visual_component* create_save_button();
    bear::gui::visual_component* create_medal( const std::string& medal );
    bear::gui::visual_component* create_score( const std::string& format );

    bool on_close();
    void on_save_button();

  private:
    /** \brief The text control receiving the name of the player. */
    bear::gui::text_input* m_text;

    /** \brief The table in which the scores are stored. */
    score_table& m_score_table;

    /** \brief The score of the player. */
    double m_score;

    /** \brief The level to load. */
    std::string m_next_level;

    /** \brief Tell if there is a record or not. */
    const bool m_new_record;

    /** \brief The last name entered in the instances of this class. */
    static std::string s_player_name;

  }; // class frame_level_score
} // namespace ptb

#endif // __PTB_FRAME_LEVEL_SCORE_HPP__
