/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A camera shared among the players.
 * \author Julien Jorge
 */
#ifndef __PTB_SHARED_CAMERA_HPP__
#define __PTB_SHARED_CAMERA_HPP__

#include "ptb/player_proxy.hpp"

#include "communication/typed_message.hpp"
#include "engine/messageable_item.hpp"
#include "generic_items/camera.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A camera shared among the players.
   * \author Julien Jorge
   */
  class shared_camera:
    public bear::engine::messageable_item<bear::camera>
  {
    DECLARE_BASE_ITEM(shared_camera);

  public:
    typedef bear::engine::messageable_item<bear::camera> super;

    /*----------------------------------------------------------------------*/
    /**
     * \brief The different placement modes for the camera.
     */
    enum placement_mode
      {
        /** \brief Centered on the first player. */
        lock_first_player,

        /** \brief Centered on the second player. */
        lock_second_player,

        /** \brief Centered between the two players. */
        shared,

        /** \brief Don't move. */
        do_nothing
      }; // enum mode

    /*----------------------------------------------------------------------*/
    /**
     * \brief A message that set the placement mode of the camera.
     * \author Julien Jorge
     */
    class set_placement_message:
      public bear::communication::typed_message<shared_camera>
    {
    public:
      set_placement_message( placement_mode mode );

      bool apply_to( shared_camera& that );

    private:
      /** \brief The mode to set. */
      const placement_mode m_mode;

    }; // class set_placement_message

  private:
    /** \brief The type of the progress function. */
    typedef
    void (shared_camera::*progress_type)( bear::universe::time_type );

    /*----------------------------------------------------------------------*/
  public:
    shared_camera();

    void build();
    void progress( bear::universe::time_type elapsed_time );

    void set_mode( placement_mode mode );

  private:
    void auto_position( bear::universe::time_type elapsed_time );

    void set_first_player( bear::universe::time_type elapsed_time );
    void set_second_player( bear::universe::time_type elapsed_time );
    void set_shared( bear::universe::time_type elapsed_time );
    void search_players();

    void progress_no_players( bear::universe::time_type elapsed_time );
    void progress_with_players( bear::universe::time_type elapsed_time );

  private:
    /** \brief Current placement mode. */
    placement_mode m_placement;

    /** \brief The first player. */
    player_proxy m_first_player;

    /** \brief The second player. */
    player_proxy m_second_player;

    /** \brief The current progress method. */
    progress_type m_progress;

  }; // class shared_camera
} // namespace ptb

#endif // __PTB_SHARED_CAMERA_HPP__
