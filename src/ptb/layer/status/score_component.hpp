/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The component to display the score.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_SCORE_COMPONENT_HPP__
#define __PTB_SCORE_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"

#include "visual/writing.hpp"

namespace ptb
{
  /**
   * \brief The component to display the score.
   * \author Sebastien Angibaud
   */
  class score_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  public:
    score_component
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
    void on_score_changed(unsigned int s);

  private:
    /** \brief The font for text. */
    bear::visual::font m_font;
    
    /** \brief The score. */
    bear::visual::writing m_score;

  }; // class score_component
} // namespace ptb

#endif // __PTB_SCORE_COMPONENT_HPP__
