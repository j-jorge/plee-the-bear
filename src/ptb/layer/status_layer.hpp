/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The status layer contains the area where are printed the score,
 *        energy, remaining lifes of the players.
 * \author Julien Jorge
 */
#ifndef __PTB_STATUS_LAYER_HPP__
#define __PTB_STATUS_LAYER_HPP__

#include "ptb/layer/status/status_component.hpp"
#include "ptb/layer/status/time_component.hpp"

#include "ptb/gui/notification_widget.hpp"
#include "ptb/player_proxy.hpp"

#include "communication/messageable.hpp"
#include "engine/layer/gui_layer.hpp"

#include <claw/tween/tweener_group.hpp>
#include <claw/tween/tweener_sequence.hpp>

namespace ptb
{
  /**
   * \brief The status layer contains the area where are printed the score,
   *        energy, remaining lifes of the players.
   */
  class status_layer:
    public bear::communication::messageable,
    public bear::engine::gui_layer
  {
  public:
    /** \brief The type of a list of scene elements retrieved from the layer.*/
    typedef bear::engine::gui_layer::scene_element_list scene_element_list;

    /** The type of the parent class. */
    typedef bear::engine::gui_layer super;

    /** The A list of status component. */
    typedef std::list<status_component*> component_list;

    /** The A map of status component. */
    typedef std::map<std::string, status_component*> component_map;

  private:
    /**
     * \brief All the informations we want to show about a player.
     */
    class player_status
    {
    public:
      player_status
      ( bear::engine::level_globals& glob, const bear::visual::font& f,
        const player_proxy& p, const bear::visual::position_type& pos_ref,
	status_component::x_placement x_p,
	const bear::universe::size_box_type& layer_size	);

      ~player_status();

      const player_proxy& get_player() const;

      void progress( bear::engine::level_globals& glob,
                     bear::universe::time_type elapsed_time );
      void render( scene_element_list& e ) const;
      void add_notification
      ( const std::string& text, const bear::visual::sprite& sp );

    private:
      void progress_notification( bear::universe::time_type elapsed_time );
      void create_notification();      
      void on_notification_position_update(double position);
      
    public:
      /** \brief Level globals. */
      bear::engine::level_globals& m_level_globals;

      /** \brief The component containing a notification. */
      notification_widget notification;

      /** \brief The offset of notification component. */
      bear::visual::coordinate_type notification_offset_y;

    private:
      /** \brief The set of current tweeners. */
      claw::tween::tweener_group m_tweeners;

      /** \brief The tweener for notification. */
      claw::tween::tweener_sequence m_notification_tweener;

      /** \brief The list of notifications. */
      std::list< std::pair<std::string,bear::visual::sprite> > m_notifications;

      /** \brief Pointer to the player. */
      player_proxy m_player;

      /** \brief The components to display. */
      component_list m_components;

    }; // class player_status

  public:
    status_layer( const std::string& name );
    virtual ~status_layer();

    void pre_cache();
    void build();
    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;

    void set_timer( const time_component::timer_handle& t );
    void set_boss( const monster* b );
    void add_notification
    ( unsigned int index, const std::string& text, 
      const bear::visual::sprite& sp );
  
  private:
    void progress_boss( bear::universe::time_type elapsed_time );
    void render_boss( scene_element_list& e ) const;

    void render_notification
    ( scene_element_list& e, const player_status* data,
      double take_width, double orientation ) const;
    
    void set_visual_shadows
    ( scene_element_list& visuals, bear::visual::coordinate_type x,
      bear::visual::coordinate_type y ) const;

    void search_players();
    void create_components();
    void create_persistent_components();
    
  private:
    /** \brief Data of the first player. */
    player_status* m_data_1;

    /** \brief Data of the second player. */
    player_status* m_data_2;

    /** \brief The component that display components. */
    component_list m_components;

    /** \brief The component that display persistent components. */
    component_map m_persistent_components;

    /** \brief The timer of the level. */
    time_component::timer_handle m_timer;

    /** \brief Distance between the elements of the layer. */
    const static unsigned int s_margin;

  }; // class status_layer
} // namespace ptb

#endif // __PTB_STATUS_LAYER_HPP__
