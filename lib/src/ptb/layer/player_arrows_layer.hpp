/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A player_arrows_layer is a layer containing the arrows of players.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_PLAYER_ARROWS_LAYER_HPP__
#define __PTB_PLAYER_ARROWS_LAYER_HPP__

#include "engine/layer/gui_layer.hpp"
#include "ptb/player_proxy.hpp"
#include "visual/writing.hpp"

namespace ptb
{
  /**
   * \brief An player_arrows_layer is a layer containing the arrows of the
   *        players.
   * \author Sebastien Angibaud
   */
  class player_arrows_layer:
    public bear::engine::gui_layer
  {
  public:
    /** \brief The type of a list of scene elements retrieved from the layer. */
    typedef bear::engine::gui_layer::scene_element_list scene_element_list;

  private:
    class player_data
    {
    public:
      player_data
      ( const claw::math::coordinate_2d<unsigned int> screen_size,
        const player_proxy& p, const bear::visual::sprite& arrow,
        const bear::visual::font& f );

      void render( scene_element_list& e ) const;
      void adjust_arrow( bear::engine::level_globals& glob,
                         const bear::universe::rectangle_type& visible_area );

    private:
      void
      adjust_position( const bear::universe::rectangle_type& visible_area );
      void adjust_angle( const bear::universe::rectangle_type& visible_area );
      void
      adjust_distance( bear::engine::level_globals& glob,
                       const bear::universe::rectangle_type& visible_area );

    private:
      /** \brief The size of the screen. */
      const claw::math::coordinate_2d<unsigned int> m_screen_size;

      /** \brief The arrow for this player. */
      bear::visual::sprite m_arrow;

      /** \brief The text displaying the distance. */
      bear::visual::writing m_distance;

      /** \brief The position of the distance text. */
      bear::universe::position_type m_distance_text_position;

      /** \brief The player. */
      player_proxy m_player;

      /** \brief Tell if the arrow is visible. */
      bool m_visible;

      /** \brief The position of the arrow. */
      bear::universe::position_type m_position;
    }; // class player_data

  public:
    player_arrows_layer();
    ~player_arrows_layer();

    void search_players( );
    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;

  private:
    /** \brief Data for the first player. */
    player_data* m_data_1;

    /** \brief Data for the second player. */
    player_data* m_data_2;

  }; // class player_arrows_layer
} // namespace ptb

#endif // __PTB_PLAYER_ARROWS_LAYER_HPP__
