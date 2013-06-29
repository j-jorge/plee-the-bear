/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a catapult.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_CATAPULT_HPP__
#define __PTB_CATAPULT_HPP__

#include "ptb/item_brick/item_with_single_player_action_reader.hpp"
#include "ptb/player_proxy.hpp"

#include "engine/model.hpp"
#include "engine/base_item.hpp"
#include "engine/export.hpp"
#include "engine/item_brick/with_expression_creation.hpp"

#include <claw/tween/tweener_sequence.hpp>

namespace ptb
{
  /**
   * \brief The class describing a catapult.
   *
   * The valid fields for this item are
   *
   * \author Sebastien Angibaud
   */
  class catapult:
    public item_with_single_player_action_reader
    < bear::engine::model<bear::engine::base_item> >,
    public bear::engine::with_linear_expression_creation
  {
    DECLARE_BASE_ITEM(catapult);

  private:
     enum catapult_state_name
      {
        idle_state = 0,
        angle_selection_state,
        force_selection_state,
	throw_state,
	end_state,
	cancel_state
      }; // enum catapult_state_name

  public:
    /** \brief The type of the parent class. */
    typedef item_with_single_player_action_reader
    < bear::engine::model<bear::engine::base_item> > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    typedef void 
    (catapult::*progress_function_type)(bear::universe::time_type);

  public:
    catapult();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    unsigned int get_state() const;

  protected:
    void get_dependent_items( std::list<physical_item*>& d ) const;

  private:
    void progress_idle( bear::universe::time_type elapsed_time );
    void progress_angle_selection( bear::universe::time_type elapsed_time );
    void progress_force_selection( bear::universe::time_type elapsed_time );
    void progress_throw( bear::universe::time_type elapsed_time );
    void progress_end_state( bear::universe::time_type elapsed_time );
    
    void start_idle();
    void start_angle_selection();
    void start_force_selection();
    void start_throw();
    void start_end_state();
    void cancel();

    void create_stop_angle_tweener();
    void create_arm_angle_tweener();
    void init_angle();
    void compute_force();

    void on_stop_angle_update(double angle);
    void on_arm_angle_update(double angle);
    void on_placement_collision
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );

    void start_action(player_action::value_type a);
    void stop_action(player_action::value_type a);

    bear::expr::linear_expression do_get_expression() const;

  private:
    static void init_exported_methods();
    
  private:
    /** \brief Current state. */
    catapult_state_name m_state;

    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief Angle of stop component. */
    double m_stop_angle;

    /** \brief Angle of arm. */
    double m_arm_angle;

    /** \brief The player on the catapult. */
    player_proxy m_player;

    /** \brief The maximal height of the player.*/
    bear::universe::coordinate_type m_maximal_height;

    /** \brief Minimal force to give.*/
    bear::universe::coordinate_type m_minimal_force;

    /** \brief Maximal force to give.*/
    bear::universe::coordinate_type m_maximal_force;

    /** \brief Force to give.*/
    bear::universe::force_type m_force;

    /** \brief The relative position of player. */
    bear::universe::position_type m_player_position;

    /** \brief The tweener for stop angle. */
    claw::tween::tweener_sequence m_stop_angle_tweener;

    /** \brief The tweener for arm angle. */
    claw::tween::tweener_sequence m_arm_angle_tweener;

    /** \brief Indicates if the jump has been cancel. */
    bool m_cancel;

    /** \brief The initial angle of stop component. */
    static const double s_initial_stop_angle;

    /** \brief The initial angle of arm component. */
    static const double s_initial_arm_angle;

    /** \brief The minimal angle of arm component. */
    static const double s_minimal_arm_angle;

    /** \brief The maximal angle of arm component. */
    static const double s_maximal_arm_angle;
  }; // class catapult
} // namespace ptb

#endif // __PTB_CATAPULT_HPP__
