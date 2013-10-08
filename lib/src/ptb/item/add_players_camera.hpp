/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief  An object that gives players to a camera_on_object item.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_ADD_PLAYERS_CAMERA_HPP__
#define __PTB_ADD_PLAYERS_CAMERA_HPP__

#include "engine/base_item.hpp"
#include "generic_items/camera_on_object.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An object that gives players item to a camera_on_object item.
   *
   * This item has no field.
   *
   * \author Sébastien Angibaud
   */
  class add_players_camera:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(add_players_camera);

  public:

    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    add_players_camera();

    void progress(bear::universe::time_type elapsed_time);
    bool set_bool_field( const std::string& name, bool value );
    bool set_item_field( const std::string& name, base_item* value );

  private:
    /** \brief Indicates if we add the first player. */
    bool m_first_player;

    /** \brief Indicates if we add the second player. */
    bool m_second_player;

    /** \brief The camera. */
    bear::camera_on_object* m_camera;
  }; // class add_players_camera
} // namespace ptb

#endif // __PTB_ADD_PLAYERS_CAMERA_HPP__
