/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A message that adds the boss in the status layer.
 * \author Julien Jorge
 */
#ifndef __PTB_STATUS_LAYER_BOSS_MESSAGE_HPP__
#define __PTB_STATUS_LAYER_BOSS_MESSAGE_HPP__

#include "ptb/layer/status_layer.hpp"

#include "communication/typed_message.hpp"

namespace ptb
{
  class monster;
  class status_layer;

  /**
   * \brief A message that adds the boss in the status layer.
   * \author Sebastien Angibaud
   */
  class status_layer_boss_message:
    public bear::communication::typed_message<status_layer>
  {
  public:
    status_layer_boss_message();

    void set_boss( monster* b );
    bool apply_to( status_layer& that );

  private:
    /** \brief Pointer to the boss. */
    monster* m_boss;

  }; // class status_layer_boss_message
} // namespace ptb

#endif // __PTB_STATUS_LAYER_BOSS_MESSAGE_HPP__
