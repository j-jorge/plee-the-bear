/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display the energy.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_ENERGY_COMPONENT_HPP__
#define __PTB_ENERGY_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"
#include "ptb/gui/horizontal_gauge.hpp"

namespace ptb
{
  /**
   * \brief The component to display the energy.
   * \author Sebastien Angibaud
   */
  class energy_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  public:
    energy_component
    ( bear::engine::level_globals& glob, const player_proxy& p, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p,
      const bear::universe::size_box_type& layer_size);

    void build();
    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;
    unsigned int width() const;
    unsigned int height() const;

  protected:
    void init_signals();

  private:
    void on_energy_changed();
    void on_energy_added(double e);
    void on_energy_removed(double e);
    void on_max_energy_added(double e);
    void on_max_energy_length_update(double length);

  private:
    /** \brief The energy. */
    horizontal_gauge m_energy;
  }; // class energy_component
} // namespace ptb

#endif // __PTB_ENERGY_COMPONENT_HPP__
