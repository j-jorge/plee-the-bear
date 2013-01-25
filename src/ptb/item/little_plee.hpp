/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a little_plee.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_LITTLE_PLEE_HPP__
#define __PTB_LITTLE_PLEE_HPP__

#include "engine/base_item.hpp"
#include "engine/model.hpp"
#include "engine/export.hpp"

#include <list>

namespace ptb
{
  /**
   * \brief The class describing a little_plee.
   * \author Sébastien Angibaud
   * The custom fields of this class are :
   *   - any field supported by the parent classes.
   */
  class little_plee:
    public bear::engine::model< bear::engine::base_item >
  {
    DECLARE_BASE_ITEM(little_plee);

  public:
     enum state
      {
        run_state,
        jump_state
      }; // enum state

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::model< bear::engine::base_item > super;

  public:
    little_plee();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void set_positive_orientation(bool orientation);
    void start();

  private:
    void progress_run();
    void progress_jump();
    void do_jump();
    void progress_idle();
    bool can_go_toward( bool positive_orientation );

  private:
    /** \brief The current_state of the item. */
    state m_current_state;

    /** \brief Indicates if life have been already given. */
    bool m_life_given;

    /** \brief Number of iteration with contact on right or left side. */
    unsigned int m_nb_idle;

  }; // class little_plee
} // namespace ptb

#endif // __PTB_LITTLE_PLEE_HPP__
