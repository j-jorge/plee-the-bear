/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display the honeypots.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_HONEYPOTS_COMPONENT_HPP__
#define __PTB_HONEYPOTS_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"

#include "visual/sprite.hpp"

namespace ptb
{
  /**
   * \brief The component to display the honeypots.
   * \author Sebastien Angibaud
   */
  class honeypots_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  public:
    honeypots_component
    ( bear::engine::level_globals& glob, const player_proxy& p, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p,
      const bear::engine::level& lvl,
      const bear::universe::size_box_type& layer_size);

    void build();
    
    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;
    unsigned int width() const;
    unsigned int height() const;
    
  private:
    void on_count_change();

  private:
    /** \brief Animation for honeypots. */
    bear::visual::sprite m_honeypot;

    /** \brief The current level. */
    const bear::engine::level& m_level;
    
    /** \brief The last number of honeypots. */
    unsigned int m_last_count;
  }; // class honeypots_component
} // namespace ptb

#endif // __PTB_HONEYPOTS_COMPONENT_HPP__
