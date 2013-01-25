/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a frog.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_FROG_HPP__
#define __PTB_FROG_HPP__

#include "ptb/item_brick/sniffable.hpp"
#include "ptb/item_brick/counted_item.hpp"

#include "engine/model.hpp"
#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a frog.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sébastien Angibaud
   */
  class frog:
    public bear::engine::model
    < counted_item < bear::engine::base_item > >,
    public sniffable
  {
    DECLARE_BASE_ITEM(frog);

  public:
    /** \brief The type of the parent class. */
    typedef  bear::engine::model
    < counted_item < bear::engine::base_item> > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    typedef void (frog::*progress_function_type)(bear::universe::time_type);

  public:
    frog();
    ~frog();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    bool set_real_field( const std::string& name, double value );

  protected:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    std::string get_picture_filename() const;
    std::string get_picture_name() const;
    std::string get_notification_text() const;
    unsigned int get_points() const;

    void progress_idle( bear::universe::time_type elapsed_time );
    void progress_jump( bear::universe::time_type elapsed_time );
    void progress_fall( bear::universe::time_type elapsed_time );
    void progress_explose( bear::universe::time_type elapsed_time );

    void start_idle();
    void start_jump();
    void start_fall();
    void start_explose();

    void apply_jump();
    void choose_idle_action();

    bool scan_no_wall_in_direction
    ( const bear::universe::position_type& origin,
      const bear::universe::vector_type& dir ) const;

    bool test_in_sky();
    bool test_bottom_contact();
    void test_explose();
    void try_to_jump();
    bool can_jump() const;
    void create_floating_score() const;

    static void init_exported_methods();

  private:
    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief Initial position. */
    bear::universe::position_type m_initial_position;

    /** \brief The maximum distance of the initial position. */
    bear::universe::coordinate_type m_max_distance;

    /** \brief The last index of player on the frog. */
    unsigned int m_last_player_index;
  }; // class frog
} // namespace ptb

#endif // __PTB_FROG_HPP__
