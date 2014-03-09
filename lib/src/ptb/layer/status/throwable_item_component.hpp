/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display the throwable_item.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_THROWABLE_ITEM_COMPONENT_HPP__
#define __PTB_THROWABLE_ITEM_COMPONENT_HPP__

#include "ptb/layer/status/status_component.hpp"
#include "ptb/layer/status/floating_bonus.hpp"

#include "visual/animation.hpp"
#include "visual/writing.hpp"

namespace ptb
{
  /**
   * \brief The component to display the throwable_item.
   * \author Sebastien Angibaud
   */
  class throwable_item_component :
    public status_component
  {
  private:
    /** \brief The type of a list of floating corrupting_bonus. */
    typedef std::list<floating_bonus> floating_bonus_list;

    typedef
    std::list< claw::memory::smart_ptr<boost::signals2::scoped_connection> >
    signal_connection_list;

  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  public:
    throwable_item_component
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
    void create_floating_bonus( const std::string& name );
    void on_power_changed( bool status, const std::string& name );
    void on_stones_stock_changed( unsigned int stock );
    void on_throwable_item_changed(const std::string& animation);
    void on_throwable_item_stock_changed(unsigned int stock);
    void on_throwable_item_changed();      

  private:
    /** \brief The font for text. */
    bear::visual::font m_font;
    
    /** \brief The throwable_item. */
    bear::visual::writing m_throwable_item;

    /** \brief The current animation of throwable_item. */
    bear::visual::animation m_throwable_item_animation;

    /** \brief map of floating corrupting bonus. */
    floating_bonus_list m_floating_bonus;

    /** The connections to the signals triggered when the bonus change. */
    signal_connection_list m_bonus_signals;

    /** The last stones count. */
    unsigned int m_stones_count;
  }; // class throwable_item_component
} // namespace ptb

#endif // __PTB_THROWABLE_ITEM_COMPONENT_HPP__
