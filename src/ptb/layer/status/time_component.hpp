/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display the time.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_TIME_COMPONENT_HPP__
#define __PTB_TIME_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"

#include "generic_items/timer.hpp"

#include "universe/derived_item_handle.hpp"

#include "visual/writing.hpp"

namespace ptb
{
  /**
   * \brief The component to display the time.
   * \author Sebastien Angibaud
   */
  class time_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

    /** \brief An handle on the timer of the level. */
    typedef
    bear::universe::const_derived_item_handle<bear::timer> timer_handle;

  public:
    time_component
    ( bear::engine::level_globals& glob, const player_proxy& p, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p, const timer_handle& t,
      const bear::universe::size_box_type& layer_size);

    void build();
    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;
    unsigned int width() const;
    unsigned int height() const;

  private:
    /** \brief The font for text. */
    bear::visual::font m_font;
    
    /** \brief The component in which we show the time. */
    bear::visual::writing m_text_time;

    /** \brief Indicate if the time must be displayed. */
    bool m_time_on;

    /** \brief The timer of the level. */
    timer_handle m_timer;
  }; // class time_component
} // namespace ptb

#endif // __PTB_TIME_COMPONENT_HPP__
