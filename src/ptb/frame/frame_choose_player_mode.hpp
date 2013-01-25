/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A frame to choose player mode (one or two players).
 * \author Sebastien Angibaud
 */
#include "ptb/frame/menu_frame.hpp"

namespace ptb
{
  /**
   * \brief A frame to choose player mode (one or two players).
   * \author Sebastien Angibaud
   */
  class frame_choose_player_mode:
    public menu_frame
  {
  public:
    frame_choose_player_mode( windows_layer* owning_layer );

  private:
    void create_controls();

    void start_game( unsigned int p ) const;
    void load_game_variables() const;
  }; // class frame_choose_player_mode
} // namespace ptb
