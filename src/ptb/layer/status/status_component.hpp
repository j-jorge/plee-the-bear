/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The base of component on status_layer.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATUS_COMPONENT_HPP__
#define __PTB_STATUS_COMPONENT_HPP__

#include "ptb/player_proxy.hpp"

#include "universe/types.hpp"
#include "universe/zone.hpp"

#include "engine/level_globals.hpp"
#include "engine/layer/gui_layer.hpp"

#include <boost/signals.hpp>
#include <claw/tween/tweener_group.hpp>

namespace ptb
{
  /**
   * \brief The base of component on status_layer.
   * \author Sebastien Angibaud
   */
  class status_component
  {
  public:
    /** \brief The type of a list of scene elements retrieved from the layer.*/
    typedef bear::engine::gui_layer::scene_element_list scene_element_list;
     
    /** \brief The type of placement on x-coordinate. */
    enum x_placement
      {
        left_placement = 0,
        middle_x_placement,
	right_placement
      }; // enum x_placement

    /** \brief The type of placement on y-coordinate. */
    enum y_placement
      {
        bottom_placement = 0,
        middle_y_placement,
	top_placement
      }; // enum y_placement

  public:
    status_component
    ( bear::engine::level_globals& glob, const player_proxy& p,
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p, 
      const bear::universe::size_box_type& layer_size);
    virtual ~status_component();
    
    virtual void build();
    virtual void progress( bear::universe::time_type elapsed_time );
    virtual void render( scene_element_list& e ) const;

    void add_signal(const boost::signals::connection& s);
    void add_tweener( const claw::tween::tweener& t);
    const bear::visual::position_type& get_position() const;
    const bear::visual::position_type& get_render_position() const;
    const bear::visual::position_type& get_active_position() const;
    const bear::visual::position_type& get_inactive_position() const;
    const player_proxy& get_player() const;
    player_proxy& get_player();
    bear::engine::level_globals& get_level_globals() const;
    const bear::universe::size_box_type& get_layer_size() const;    

    virtual unsigned int width() const = 0;
    virtual unsigned int height() const = 0;

    void update_inactive_position();
    void on_x_position_update(double x);
    void on_y_position_update(double y);

  protected:
    virtual void init_signals();

  protected:
    /** \brief The length of the bars. */
    const static double s_bar_length;

    /** \brief Distance between the elements of the layer. */
    const static unsigned int s_margin;

  private:
    /** \brief Level globals. */
    bear::engine::level_globals& m_level_globals;

    /** \brief Pointer to the player. */
    player_proxy m_player;

    /** \brief The side in which the component appears. */
    bear::universe::zone::position m_side;

    /** \brief The placement on x-coordinate. */
    x_placement m_x_placement;

    /** \brief The placement on y-coordinate. */
    y_placement m_y_placement;

    /** \brief The size of the layer. */
    bear::universe::size_box_type m_layer_size;

    /** \brief The set of current tweeners. */
    claw::tween::tweener_group m_tweeners;

    /** \brief Current position of the component. */
    bear::visual::position_type m_position;

    /** \brief Current position of the component for rendering. */
    bear::visual::position_type m_render_position;

    /** \brief Position of the component when it is active. */
    bear::visual::position_type m_active_position;

    /** \brief Position of the component when it is inactive. */
    bear::visual::position_type m_inactive_position;
    
    /** \brief The connections to various signals. */
    std::list<boost::signals::connection> m_signals;

  }; // class status_component
} // namespace ptb

#endif // __PTB_STATUS_COMPONENT_HPP__
