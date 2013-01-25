/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a spider.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_SPIDER_HPP__
#define __PTB_SPIDER_HPP__

#include "ptb/item_brick/counted_enemy.hpp"
#include "ptb/item_brick/monster.hpp"
#include "ptb/player_proxy.hpp"

#include "engine/model.hpp"
#include "engine/export.hpp"

#include "universe/link/link.hpp"

#include "generic_items/reference_item.hpp"
#include "generic_items/link/continuous_link_visual.hpp"

namespace ptb
{
  /**
   * \brief The class describing a spider.
   *
   * The valid fields for this item are
   *  - \a max_walk_distance: The maximum distance with start position
   * in walk state (default=200).
   *  - \a max_spider_silk_length: Length of spider silk (default=300).
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class spider:
    public counted_enemy< bear::engine::model<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(spider);

  public:
    /** \brief The type of the parent class. */
    typedef counted_enemy
    < bear::engine::model<bear::engine::base_item> > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    typedef void (spider::*progress_function_type)(bear::universe::time_type);

  public:
    spider();
    ~spider();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    bool set_real_field( const std::string& name, double value );

  protected:
    void inform_no_energy(const monster& attacker);
    void injure
    ( const monster& attacker, bear::universe::zone::position side,
      double duration);
    void leaves_active_region();

  private:
    std::string get_picture_filename() const;
    std::string get_picture_name() const;
    std::string get_notification_text() const;

    void progress_walk( bear::universe::time_type elapsed_time );
    void progress_throw_venom( bear::universe::time_type elapsed_time );
    void progress_dangle( bear::universe::time_type elapsed_time );
    void progress_dead( bear::universe::time_type elapsed_time );

    void start_walk();
    void start_throw_venom();
    void start_dangle();
    void start_dead();

    void go_up();
    void throw_venom();

    bool scan(bool& player_at_right, bool& player_at_left);
    bool scan_for_player
    ( const player_proxy& p, bool& player_at_right,
      bool& player_at_left ) const;
    bool scan_no_wall_in_direction
    ( const bear::universe::position_type& origin,
      const bear::universe::vector_type& dir ) const;
    void create_silk_link(base_item* ref);
    void create_link_visual(base_item* ref);
    void create_silk_reference_item();
    bear::engine::base_item* create_dead_reference_item();

  protected:
    void to_string( std::string& str ) const;

  private:
    static void init_exported_methods();

  private:
    /** \brief The energy of the soul of an spider.*/
    static const unsigned int s_soul_energy;

    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief The position of the origin. */
    bear::universe::position_type m_origin_position;

    /** \brief The maximum distance with origin position in walk state. */
    bear::universe::coordinate_type m_max_walk_distance;

    /** \brief The length of spider silk.*/
    bear::universe::coordinate_type m_spider_silk_length;

    /** \brief Indicates if spider go up.*/
    bool m_go_up;

    /** \brief Indicates if spider has started dangle state.*/
    bool m_dangle_state;

    /** \brief The reference item for compute silk link.*/
    bear::reference_item* m_silk_reference_item;

    /** \brief The decoration of the link.. */
    bear::continuous_link_visual* m_link_visual;

    /** \brief The link in dangle state.*/
    bear::universe::link* m_link;
  }; // class spider
} // namespace ptb

#endif // __PTB_SPIDER_HPP__
