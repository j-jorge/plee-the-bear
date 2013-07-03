/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame is the start menu (where we choose the mode of the game).
 * \author Julien Jorge
 */
#include "ptb/frame/menu_frame.hpp"
#include "ptb/playability_type.hpp"

namespace ptb
{
  /**
   * \brief This frame is the start menu (where we choose the mode of the game).
   * \author Julien Jorge
   */
  class frame_start_menu:
    public menu_frame
  {
  public:
    frame_start_menu
    ( windows_layer* owning_layer, bool use_loading,
      playability_type::value_type playability );

  private:
    void create_controls();

    void start_game( unsigned int p ) const;

  private:
    /** \brief Tell if we use the "loading" level. */
    bool m_use_loading;

    /** \brief The playability of the level : number of players. */
    playability_type::value_type m_playability;

  }; // class frame_start_menu
} // namespace ptb
