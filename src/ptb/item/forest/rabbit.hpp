/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a rabbit.
 * \author Sébastien Angibaud
 * \author Julien Jorge
 */
#ifndef __PTB_RABBIT_HPP__
#define __PTB_RABBIT_HPP__

#include "ptb/player_proxy.hpp"
#include "ptb/item_brick/sniffable.hpp"
#include "ptb/item_brick/item_with_attack_point.hpp"
#include "ptb/item_brick/counted_item.hpp"

#include "engine/model.hpp"
#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a rabbit.
   *
   * The valid fields for this item are
   * - max_distance (real): The maximum horizontal distance from its initial
   *   position where the rabbit is allowed to go (default = 500),
   * - any field supported by the parent classes.
   *
   * \author Sébastien Angibaud
   * \author Julien Jorge
   */
  class rabbit:
    public item_with_attack_point
    < bear::engine::model< counted_item < bear::engine::base_item>  > >,
    public sniffable
  {
    DECLARE_BASE_ITEM(rabbit);

  public:
    /** \brief The type of the parent class. */
    typedef item_with_attack_point
    < bear::engine::model
      < counted_item < bear::engine::base_item> > > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    /** \brief The type of the functions used to do the progression of the
        rabbit. */
    typedef void (rabbit::*progress_function_type)(bear::universe::time_type);

  public:
    rabbit();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    bool set_real_field( const std::string& name, double value );
    bool set_bool_field( const std::string& name, bool value );

    void enters_active_region();

  protected:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    std::string get_picture_filename() const;
    std::string get_picture_name() const;
    std::string get_notification_text() const;
    unsigned int get_points() const;

    bool is_attacked_by(const player_proxy& p);
    void progress_idle( bear::universe::time_type elapsed_time );
    void progress_jump( bear::universe::time_type elapsed_time );
    void progress_fall( bear::universe::time_type elapsed_time );
    void progress_eat( bear::universe::time_type elapsed_time );
    void progress_dig( bear::universe::time_type elapsed_time );
    void progress_in_burrow( bear::universe::time_type elapsed_time );
    void progress_injured( bear::universe::time_type elapsed_time );
    void progress_walk( bear::universe::time_type elapsed_time );

    void start_idle();
    void start_fall();
    void start_eat();
    void start_dig();
    void start_in_burrow();
    void start_injured();
    void start_walk();

    void pre_jump();
    void walk( bear::universe::time_type duration );

    void apply_walk();
    void apply_jump();
    void choose_idle_action();

    bool scan_no_wall_in_direction
    ( const bear::universe::position_type& origin,
      const bear::universe::vector_type& dir ) const;

    bool test_in_sky();
    void try_to_move();
    bool can_move_forward() const;

    void create_floating_score( unsigned int index ) const;

    static void init_exported_methods();

  private:
    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief Initial position. */
    bear::universe::position_type m_initial_position;

    /** \brief The maximum distance of the initial position. */
    bear::universe::coordinate_type m_max_distance;

    /** \brief Indicates if the rabbit is injured. */
    bool m_injured;

    /** \brief How long the opacity effect has been applied. */
    bear::universe::time_type m_opacity_effect_duration;

    /** \brief The opacity applied to the sprites when the rabbit is injured.*/
    double m_opacity_injured;

    /** \brief The increment added at each iteration to m_opacity_injured. */
    double m_opacity_inc;

    /** \brief Indicates if the rabbit has a carrot. */
    bool m_has_carrot;

    /** \brief The remaining time to spend in the current action. */
    bear::universe::time_type m_remaining_action_time;

    /** \brief Tell if the rabbit is a marionette, 
	in which case he won't decide is actions himself. */
    bool m_marionette;

  }; // class rabbit
} // namespace ptb

#endif // __PTB_RABBIT_HPP__
