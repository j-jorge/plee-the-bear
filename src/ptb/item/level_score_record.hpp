/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A toggle to manage the score table of a level.
 * \author Julien Jorge
 */
#ifndef __PTB_LEVEL_SCORE_RECORD_HPP__
#define __PTB_LEVEL_SCORE_RECORD_HPP__

#include "engine/item_brick/item_with_toggle.hpp"
#include "engine/base_item.hpp"
#include "engine/item_brick/with_linear_expression_assignment.hpp"

#include "ptb/score_table.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A toggle to manage the score table of a level.
   *
   * The custom fields of this class are:
   * - maximize (bool), tell if the goal is to maximize the score
   *   (default = true),
   * - medal.gold (real), the minimal value of the score to win the gold medal
   *   (default = 0),
   * - medal.silver (real), the minimal value of the score to win the silver
   *   medal (default = 0),
   * - medal.bronze (real), the minimal value of the score to win the bronze
   *   medal,
   * - next_level (string), the path to the next level to load (default = none),
   * - window_layer (string), the window layer in which the frame asking for the
   *   player name is shown (default = none),
   * - score_format (string), how to format the score at the end of the level
   *   (defalt = "%v"),
   * - any field supported by the parent class.
   *
   * \author Julien Jorge
   */
  class level_score_record:
    public bear::engine::item_with_toggle
  < bear::engine::base_item >,
    public bear::engine::with_linear_expression_assignment
  {
    DECLARE_BASE_ITEM(level_score_record);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_toggle< bear::engine::base_item > super;

  public:
    level_score_record();

    void build();

    bool set_string_field( const std::string& name, const std::string& value );
    bool set_bool_field( const std::string& name, bool value );
    bool set_real_field( const std::string& name, double value );

  private:
    void on_toggle_on(bear::engine::base_item *activator);
    void do_set_expression( const bear::expr::linear_expression& e );

  private:
    /** \brief The table containing the scores for this level. */
    score_table m_score_table;

    /** \brief The score of the player. */
    bear::expr::linear_expression m_value;

    /** \brief The path to the next level. */
    std::string m_next_level;

    /** \brief The window layer in which we ask the name of the player. */
    std::string m_window_layer;

    /** \brief How to format the score shown at the end of the level. */
    std::string m_score_format;

    /** \brief Indicates if the goal is to maximize the score. */
    bool m_maximize_score;

    /** \brief The minimal value to get the gold medal. */
    double m_gold;

    /** \brief The minimal value to get the silver medal. */
    double m_silver;

    /** \brief The minimal value to get the bronze medal. */
    double m_bronze;

  }; // class level_score_record
} // namespace ptb

#endif // __PTB_LEVEL_SCORE_RECORD_HPP__
