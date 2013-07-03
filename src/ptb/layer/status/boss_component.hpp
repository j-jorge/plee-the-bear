/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display a boss of a zone.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_BOSS_COMPONENT_HPP__
#define __PTB_BOSS_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"
#include "ptb/gui/horizontal_gauge.hpp"
#include "universe/derived_item_handle.hpp"

namespace ptb
{
  class monster;

  /**
   * \brief The component to display a boss of a zone.
   * \author Sebastien Angibaud
   */
  class boss_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

    /** \brief An handle on a monster. */
    typedef bear::universe::const_derived_item_handle<monster> monster_handle;
    
  public:
    boss_component
    ( bear::engine::level_globals& glob, const player_proxy& p, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p,
      const monster_handle& m,
      const bear::universe::size_box_type& layer_size );

    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;
    unsigned int width() const;
    unsigned int height() const;
     
  private:
    /** \brief The boss whose energy is displayed. */
    monster_handle m_boss;

    /** \brief Level of energy for the boss. */
    horizontal_gauge m_boss_energy;
  }; // class boss_component
} // namespace ptb

#endif // __PTB_BOSS_COMPONENT_HPP__
