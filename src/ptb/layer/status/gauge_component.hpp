/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The component to display a gauge of a zone.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_GAUGE_COMPONENT_HPP__
#define __PTB_GAUGE_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"
#include "ptb/gui/vertical_gauge.hpp"

namespace ptb
{
  /**
   * \brief The component to display a gauge of a zone.
   * \author Sebastien Angibaud
   */
  class gauge_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  public:
    gauge_component
    ( bear::engine::level_globals& glob, const player_proxy& p, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p,
      const std::string& level_sprite, const std::string& icon_sprite,
      const bear::universe::size_box_type& layer_size );

    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;
    unsigned int width() const;
    unsigned int height() const;

    void on_enters_zone();
    void on_leaves_zone();
    
  protected:
    vertical_gauge& get_gauge();
     
  private:
    /** \brief The gauge. */
    vertical_gauge m_gauge;
  }; // class gauge_component
} // namespace ptb

#endif // __PTB_GAUGE_COMPONENT_HPP__
