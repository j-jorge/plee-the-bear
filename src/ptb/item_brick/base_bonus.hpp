/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A base_bonus.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BASE_BONUS_HPP__
#define __PTB_BASE_BONUS_HPP__

#include "ptb/item_brick/sniffable.hpp"

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  class player_proxy;

  /**
   * \brief A item that contains a bonus.
   *
   * The valid fields for this item are
   *  - \a player_index : (unsigned int) Index of player that can take
   * the bonus (0 if all players)
   *  - \a type: (string) \b [required] the type of the bonus
   *      - "air_power"
   *      - "fire_power"
   *      - "water_power"
   *      - "invincibility_power"
   *      - "stones_stock"
   *      - "stones_big_stock"
   *      - "one_more_life"
   *  - \a stock: (real) the quantity provided by the box (default = auto),
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class base_bonus:
    public bear::engine::basic_renderable_item< bear::engine::base_item>,
    public sniffable
  {
  public:
    /** \brief The type of the parent class. */
    typedef
    bear::engine::basic_renderable_item<bear::engine::base_item> super;

    enum base_bonus_type
      {
        unknown_type = 0,
        air_power,
        fire_power,
        water_power,
        invincibility_power,
        stones_stock,
        stones_big_stock,
        one_more_life,
        increase_max_energy,
        switch_players
      }; // enum base_bonus_type

  public:
    base_bonus();

    void build();

    bool set_real_field( const std::string& name, double value );
    bool set_u_integer_field( const std::string& name, unsigned int value );
    bool set_string_list_field
    ( const std::string& name, const std::vector<std::string>& value );

    bool is_valid() const;

    void progress( bear::universe::time_type elapsed_time );
    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;

    bool get_bonus_given() const;
    base_bonus_type get_type() const;
    void set_type(base_bonus_type t);
    void add_type(base_bonus_type t);
    unsigned int get_stock() const;
    void set_stock(unsigned int stock);
    void set_player_index(unsigned int index);
    unsigned int get_player_index() const;

    const bear::visual::animation& get_animation() const;
    void set_animation(const bear::visual::animation& anim);

    static base_bonus_type type_from_string( const std::string& t );
    static std::string type_to_string( base_bonus_type t );

  protected:
    void to_string( std::string& str ) const;
    void give_bonus(const player_proxy& p);

  private:
    void create_little_plee(bool plee_orientation);

    virtual void do_set_type(base_bonus_type t);
    void give_max_energy(const player_proxy& p);
    void send_energy_notification(unsigned int index);
    
  private:
    /** \brief The type of the base_bonus. */
    std::vector<base_bonus_type> m_type;

    /** \brief The current type of the bonus. */
    std::size_t m_current_type;

    /** \brief Index of player that can take the bonus (0 if all players). */
    unsigned int m_player_index;

    /** \brief The delay before changing the bonus. */
    bear::universe::time_type m_change_interval;

    /** \brief Elapsed time since the creation of the item. */
    bear::universe::time_type m_elapsed_time;

    /** \brief The quantity of the bonus. */
    unsigned int m_stock;

    /** \brief Indicates if the bonus is already given. */
    bool m_bonus_given;

    /** \brief The animation played when the base_bonus is activated. */
    bear::visual::animation m_animation;

  }; // class base_bonus
} // namespace ptb

#endif // __PTB_BASE_BONUS_HPP__
