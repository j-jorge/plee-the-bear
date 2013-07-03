/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display the lives.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_LIVES_COMPONENT_HPP__
#define __PTB_LIVES_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"

#include "visual/sprite.hpp"
#include "visual/writing.hpp"

namespace ptb
{
  /**
   * \brief The component to display the lives.
   * \author Sebastien Angibaud
   */
  class lives_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  public:
    lives_component
    ( bear::engine::level_globals& glob, const player_proxy& p, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p,
      const bear::universe::size_box_type& layer_size);

    void build();
    void render( scene_element_list& e ) const;
    unsigned int width() const;
    unsigned int height() const;

  protected:
    void init_signals();

  private:
    void on_lives_changed(unsigned int s);
    void on_lives_scale_update(double scale);
    
  private:
    /** \brief The font for text. */
    bear::visual::font m_font;
    
    /** \brief The lives. */
    bear::visual::writing m_lives;

    /** \brief A small Plee next to the remaining lives. */
    bear::visual::sprite m_small_player;

    /** \brief The scale of lives writing. */
    double m_lives_scale;

  }; // class lives_component
} // namespace ptb

#endif // __PTB_LIVES_COMPONENT_HPP__
