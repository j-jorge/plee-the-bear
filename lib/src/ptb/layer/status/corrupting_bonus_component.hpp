/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display the corrupting_bonus.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_CORRUPTING_BONUS_COMPONENT_HPP__
#define __PTB_CORRUPTING_BONUS_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"
#include "ptb/layer/status/floating_corrupting_bonus.hpp"

#include "visual/sprite.hpp"
#include "visual/writing.hpp"

#include <list>

namespace ptb
{
  /**
   * \brief The component to display the corrupting_bonus.
   * \author Sebastien Angibaud
   */
  class corrupting_bonus_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  private:
    /** \brief The type of a list of floating corrupting_bonus. */
    typedef std::list<floating_corrupting_bonus> floating_corrupting_bonus_list;

  public:
    corrupting_bonus_component
    ( bear::engine::level_globals& glob, const player_proxy& p, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p,
      const bear::universe::size_box_type& layer_size,
      bool auto_disappear );

    void build();
    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;
    unsigned int width() const;
    unsigned int height() const;

  protected:
    void init_signals();

  private:    
    void on_corrupting_bonus_updated(unsigned int value);
    void on_corrupting_bonus_added();
    void on_corrupting_bonus_scale_update(double scale);
    void move();
    void change_scale();
    void create_floating_corrupting_bonus();

  private:
    /** \brief The font for text. */
    bear::visual::font m_font;
    
    /** \brief Animation for corrupting bonus. */
    bear::visual::animation m_corrupting_bonus;

    /** \brief The component in which we show the corrupting bonus count. */
    bear::visual::writing m_text_corrupting_bonus;

    /** \brief The last number of corrupting bonus. */
    unsigned int m_last_corrupting_bonus_count;

    /** \brief Scale of the corrupting bonus writing. */
    double m_corrupting_bonus_scale;

    /** \brief map of floating corrupting bonus. */
    floating_corrupting_bonus_list m_floating_corrupting_bonus;

  }; // class corrupting_bonus_component
} // namespace ptb

#endif // __PTB_CORRUPTING_BONUS_COMPONENT_HPP__
