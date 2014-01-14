/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a player.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_PLAYER_HPP__
#define __PTB_PLAYER_HPP__

#include "ptb/gauge.hpp"
#include "ptb/player_physics.hpp"
#include "ptb/player_signals.hpp"

#include "ptb/item_brick/item_with_single_player_action_reader.hpp"
#include "ptb/item_brick/item_that_speaks.hpp"
#include "ptb/item_brick/monster_item.hpp"
#include "ptb/throwable_item/throwable_items_container.hpp"

#include "engine/messageable_item.hpp"
#include "engine/model.hpp"
#include "communication/typed_message.hpp"

#include <set>
#include <list>

#include "engine/export.hpp"

namespace ptb
{
  class corrupting_bonus_attractor;
  class throwable_item;
  class state_player;
  class stone;

  /**
   * \brief The class describing a player.
   * \author Sebastien Angibaud
   */
  class player :
    public item_with_single_player_action_reader
    < item_that_speaks
      < monster_item
        < bear::engine::model
          < bear::engine::messageable_item
            < bear::engine::base_item > > > > >
  {
  public:
    /** \brief The type of the parent class. */
    typedef item_with_single_player_action_reader
    < item_that_speaks
      < monster_item
        < bear::engine::model
          < bear::engine::messageable_item
            < bear::engine::base_item > > > > > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  protected:
    enum player_state_name
      {
        walk_state = 0,
        idle_state,
        jump_state,
        fall_state,
        dead_state,
        game_over_state,
        roar_state,
        run_state,
        slap_state,
        start_jump_state,
        vertical_jump_state,
        look_upward_state,
        crouch_state,
        captive_state,
        throw_state,
        maintain_state,
        wait_state,
        injured_state,
        start_cling_state,
        cling_state,
        clung_jump_state,
        start_hang_state,
        hang_state,
        swimming_state,
        sink_state,
        float_state,
        paralyze_state
      }; // enum player_state_name

  private:
    typedef void (player::*progress_function_type)(bear::universe::time_type);

  public:
    explicit player( const player_physics& physics );
    player(const player& p);
    void init();
    virtual ~player();

    void progress( bear::universe::time_type elapsed_time );
    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;
    void pre_cache();
    void on_enters_layer();

    bool is_valid() const;
    bool set_u_integer_field( const std::string& name, unsigned int value );

    void save_position( const bear::universe::position_type& p );
    void save_current_position();

    void start_action( player_action::value_type a );
    void do_action
    ( bear::universe::time_type elapsed_time, player_action::value_type a );
    void stop_action( player_action::value_type a );
    void start_action_model(const std::string& action);

    void set_authorized_action(player_action::value_type a, bool value);
    void authorize_action( const std::string& a );
    void authorize_all_actions();
    void disable_all_actions();

    // The full namespace is used for the return type to ease the automatic
    // generation of the player_proxy class
    const ptb::gauge& get_oxygen_gauge() const;
    const ptb::gauge& get_cold_gauge() const;
    const ptb::gauge& get_heat_gauge() const;

    ptb::player_signals& get_signals();
    double get_jump_time_ratio() const;
    void update_throw_time_ratio();
    void set_throw_down(bool value);
    void set_throw_up(bool value);
    void throw_hazelnut();

    // The full namespace is used for the return type to ease the automatic
    // generation of the player_proxy class
    const ptb::throwable_items_container& get_throwable_items() const;
    ptb::throwable_items_container& get_throwable_items() ;

    bool is_a_marionette() const;
    void set_marionette( bool b);

    void set_air_float(bool status);

    void set_status_look_upward(bool status);
    bool get_status_look_upward() const;
    void set_status_crouch(bool status);
    bool get_status_crouch() const;
    void do_start_look_upward();
    void do_start_crouch();
    void do_start_throw();
    void set_can_cling(bool status);
    bool is_clung() const;
    void set_want_clung_jump(bool status);
    bool want_clung_jump() const;

    virtual void set_invincible(const bool invincible);
    void receive_energy(double energy);
    void remove_energy(const monster& attacker, double energy );
    void has_attacked(const monster& other);
    void receive_oxygen(double oxygen);
    void give_one_up();

    void add_air_stone(stone* s);
    void remove_air_stone(stone* s);
    void set_can_throw_power(bool b, monster::attack_type a);
    bool can_throw_power(const monster::attack_type a) const;

    bear::universe::position_type hot_spot() const;
    unsigned int get_index() const;
    void set_index( unsigned int index );

    void set_spot_minimum
    ( bear::universe::coordinate_type x, bear::universe::coordinate_type y );
    void set_spot_maximum
    ( bear::universe::coordinate_type x, bear::universe::coordinate_type y );
    void set_spot_balance_move
    ( bear::universe::coordinate_type x, bear::universe::coordinate_type y );

    void add_spot_gap( const bear::universe::position_type& gap );
    void balance_spot( bool x, bool y );
    void stop();

  public:
    void apply_change_object();
    void apply_move_right();
    void apply_move_left();
    void apply_impulse_jump();
    void apply_jump();
    void apply_continue_jump();
    void apply_start_jump();
    void apply_vertical_jump();
    void apply_fall();
    virtual void apply_idle();
    void apply_walk();
    void apply_run();
    void apply_slap();
    void apply_attack();
    void apply_captive();
    void apply_release();
    void apply_injured();
    void apply_paralyze(bear::universe::time_type duration);
    void apply_throw();
    void apply_maintain();
    void apply_throw_object();
    void apply_blast_stone();
    void apply_wait();
    void apply_crouch();
    void apply_look_upward();
    void apply_die();
    void apply_roar();
    void apply_disappear();
    void apply_game_over();
    void lose_in_contest_mode();
    void apply_start_cling();
    void apply_cling();
    void apply_clung_jump();
    void apply_start_hang();
    void apply_hang();
    void apply_swimming();
    void apply_swim_in_float();
    void apply_swim_up_in_float();
    void apply_sink();
    void apply_swim_up();
    void apply_swim_down();
    void apply_float();
    void apply_swim_jump();
    void apply_dive();
    void apply_sniff();

    virtual void choose_wait_state();
    virtual void choose_idle_state();
    virtual void choose_walk_state();
    virtual bear::universe::coordinate_type get_vertical_jump_force() const = 0;

  protected:
    virtual void inform_no_energy(const monster& attacker);
    virtual void injure
    ( const monster& attacker, bear::universe::zone::position side,
      double duration );
    virtual void finish_injure();
    virtual unsigned int get_offensive_coefficient
    ( unsigned int index, const monster& other,
      bear::universe::zone::position side ) const;
    virtual void progress_in_water(bear::universe::time_type elapsed_time);

    void to_string( std::string& str ) const;

  private:
    void counter_slope_reaction();

    bear::universe::coordinate_type get_move_force() const;
    bear::universe::coordinate_type get_move_force_in_walk() const;
    bear::universe::coordinate_type
    scale_ground_force( bear::universe::coordinate_type f ) const;

    void progress_walk( bear::universe::time_type elapsed_time );
    void progress_idle( bear::universe::time_type elapsed_time );
    virtual void progress_continue_idle
    ( bear::universe::time_type elapsed_time );
    void progress_jump( bear::universe::time_type elapsed_time );
    void progress_fall( bear::universe::time_type elapsed_time );
    void progress_dead( bear::universe::time_type elapsed_time );
    void progress_game_over( bear::universe::time_type elapsed_time );
    void progress_roar( bear::universe::time_type elapsed_time );
    void progress_run( bear::universe::time_type elapsed_time );
    void progress_slap( bear::universe::time_type elapsed_time );
    void progress_start_jump( bear::universe::time_type elapsed_time );
    void progress_vertical_jump( bear::universe::time_type elapsed_time );
    void progress_crouch( bear::universe::time_type elapsed_time );
    void progress_look_upward( bear::universe::time_type elapsed_time );
    void progress_captive( bear::universe::time_type elapsed_time );
    void progress_throw( bear::universe::time_type elapsed_time );
    void progress_maintain( bear::universe::time_type elapsed_time );
    void progress_wait( bear::universe::time_type elapsed_time );
    void progress_start_cling( bear::universe::time_type elapsed_time );
    void progress_cling( bear::universe::time_type elapsed_time );
    void progress_clung_jump( bear::universe::time_type elapsed_time );
    void progress_start_hang( bear::universe::time_type elapsed_time );
    void progress_hang( bear::universe::time_type elapsed_time );
    void progress_swimming( bear::universe::time_type elapsed_time );
    void progress_sink( bear::universe::time_type elapsed_time );
    void progress_float( bear::universe::time_type elapsed_time );
    void progress_injured( bear::universe::time_type elapsed_time );
    void progress_paralyze( bear::universe::time_type elapsed_time );

    void set_state(player_state_name state);
    bool is_crushed() const;
    void regenerate();
    bool is_in_floating() const;
    bool has_a_power() const;
    bool has_all_powers() const;

    void update_orientation();
    void update_power( bool b, monster::attack_type a);
    void update_powers();

    void do_get_camera();
    void do_stop_look_upward();
    void do_stop_crouch();
    void progress_spot( bear::universe::time_type elapsed_time );
    void progress_corrupting_bonus_attractor
    ( bear::universe::time_type elapsed_time );
    void progress_gauges( bear::universe::time_type elapsed_time );
    void progress_oxygen_gauge( bear::universe::time_type elapsed_time );
    void progress_heat_gauge( bear::universe::time_type elapsed_time );
    void progress_cold_gauge( bear::universe::time_type elapsed_time );

    bool test_walk();
    bool test_bottom_contact();
    bool test_in_sky_or_swimm();
    void brake();
    void create_bubble();
    void create_soul_decoration();
    void create_corrupting_bonus_attractor();
    void create_power_effect();
    void roar_shake();
    void shake(double force, bear::universe::time_type duration) const;
    virtual bear::visual::sprite get_soul_sprite() const;
    bear::universe::force_type get_object_force() const;

    void render_halos
    ( std::list<bear::engine::scene_visual>& visuals ) const;
    void render_jump_halo
    ( std::list<bear::engine::scene_visual>& visuals ) const;
    void render_hand_halo
    ( std::list<bear::engine::scene_visual>& visuals ) const;
    void render_throw
    ( std::list<bear::engine::scene_visual>& visuals ) const;
    void get_visuals_without_invincibility
    ( std::list<bear::engine::scene_visual>& visuals ) const;
    void progress_invincibility( bear::universe::time_type elapsed_time );
    void progress_air_float( bear::universe::time_type elapsed_time );

    void create_hit_star( const bear::engine::base_item& that ) const;
    void create_invincible_star();

    void fill_throwable_items();

    void add_corrupting_item
    ( double amount, double coeff, const std::string& anim );
    void remove_corrupting_item();

    void on_slap_collision
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );

    static void init_exported_methods();

  private:
    /** \brief Number of oxygen's units. */
    static const double s_max_oxygen_gauge;

    /** \brief Number of fire's units in gauge. */
    static const double s_max_heat_gauge;

    /** \brief Number of ice's units in gauge. */
    static const double s_max_cold_gauge;

  protected:
    /** \brief Number of actions of the state named "wait". */
    unsigned int m_wait_state_number;

    /** \brief The current state. */
    player_state_name m_current_state;

  private:
    /** \brief The physics constants applied to this player. */
    const player_physics m_physics;

    /** \brief What Player is doing. */
    player_action::value_type m_current_action;

    /** \brief Last saved position of the center of mass. */
    bear::universe::position_type m_saved_position;

    /** \brief Last bottom_left_position. */
    bear::universe::position_type m_last_bottom_left;

    /** \brief The different states of Player. */
    std::vector<state_player*> m_states;

    /** \brief The signals of the player. */
    player_signals m_signals;

    /** \brief Indicates if each action is authorized. */
    std::vector<bool> m_authorized_action;

    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief Indicates the time since the last invincibily visual. */
    double m_last_visual_time;

    /** \brief Indicates the ratio of the length of preparation of the jump. */
    double m_jump_time_ratio;

    /** \brief Indicates the ratio of the preparation of throw state. */
    double m_throw_time_ratio;

    /** \brief The gauge that manages the oxygen. */
    gauge m_oxygen_gauge;

    /** \brief The gauge that manages the cold. */
    gauge m_cold_gauge;

    /** \brief The gauge that manages the heat. */
    gauge m_heat_gauge;

    /** \brief Indicates if Player look up. */
    bool m_status_look_upward;

    /** \brief Indicates the time of the look_upward. */
    bear::universe::time_type m_look_upward_time;

    /** \brief Indicates if Player crouch. */
    bool m_status_crouch;

    /** \brief Indicates if Player can cling. */
    bool m_can_cling;

    /** \brief The orientation of the player in cling state. */
    bool m_cling_orientation;

    /** \brief Indicates if Player want to do a clumb jump. */
    bool m_want_clung_jump;

    /** \brief Indicates the duration of the paralyze state. */
    bear::universe::time_type m_paralyze_duration;

    /** \brief The animation of the halo. */
    bear::visual::animation* m_halo_animation;

    /** \brief The animation of the halo on the hand. */
    bear::visual::animation* m_halo_hand_animation;

    /** \brief The list of last visual when Player is invincible. */
    std::list< std::list<bear::engine::scene_visual> > m_last_visuals;

    /** \brief Indicates the time of the crouch. */
    bear::universe::time_type m_crouch_time;

    /** \brief Indicates the time since the state changement. */
    bear::universe::time_type m_state_time;

    /** \brief Indicates the time since player jump. */
    bear::universe::time_type m_jump_time;

    /** \brief Indicates the time since player is invincible. */
    bear::universe::time_type m_invincible_time;

    /** \brief The id of invincible effect. */
    std::size_t m_invincible_id_effect;

    /** \brief Indicates if Player want to throw up. */
    bool m_throw_up;

    /** \brief Indicates if Player want to throw down. */
    bool m_throw_down;

    /** \brief Indicates if Player is lazy. */
    bool m_lazy;

    /** \brief The map of current air stones. */
    std::set<stone*> m_air_stones;

    /** \brief Indicates if Player wants to move to the right. */
    bool m_move_right;

    /** \brief Indicates if Player wants to move to the left. */
    bool m_move_left;

    /** \brief Indicates that we must force right orientation. */
    bool m_force_orientation_right;

    /** \brief Indicates that we must force left orientation. */
    bool m_force_orientation_left;

    /** \brief The current force in y axis when Player jumps. */
    bear::universe::coordinate_type m_jump_force;

    /** \brief The index of this player. */
    unsigned int m_index;

    /** \brief The number of succesive iteration for which this player
        has a bottom contact. */
    unsigned int m_nb_bottom_contact;

    /** \brief The number of item that controls Player. */
    unsigned int m_controller_number;

    /** \brief Indicates if Player float in air. */
    bool m_air_float;

    /** \brief Indicates if Player want to change orientation in injure. */
    bool m_injured_orientation;

    /** \brief The set of items that Player can throw */
    throwable_items_container m_throwable_items;

    /** \brief The time since the last change of air float status. */
    bear::universe::time_type m_air_float_time;

    /** \brief The animation to display in the hand. */
    bear::visual::animation m_animation_to_throw;

    /** \brief Position of the hot spot, relative to the center of mass. */
    bear::universe::position_type m_hot_spot_position;

    /** \brief Minimum acceptable value for the position of the hot spot. */
    bear::universe::position_type m_hot_spot_minimum;

    /** \brief Maximum acceptable value for the position of the hot spot. */
    bear::universe::position_type m_hot_spot_maximum;

    /** \brief Maximum movement allowed when balancing the hot spot. */
    bear::universe::position_type m_hot_spot_balance_move;

    /** \brief A map that indicates if Player can throw a power. */
    std::map<monster::attack_type, bool> m_can_throw_power;

    /** \brief Pointer on the corrupting bonus attractor of the player. */
    corrupting_bonus_attractor* m_corrupting_bonus_attractor;

    /** \brief Number of oxygen's units loss in the water during one second. */
    static const double s_oxygen_loss_speed;

    /** \brief Number of oxygen's units won in the water during one second. */
    static const double s_oxygen_inspiration_speed;

    /** \brief Number of fire's units loss in the fire environment
     * during one second. */
    static const double s_fire_loss_speed;

    /** \brief Number of fire's units won in the fire environment
     * during one second. */
    static const double s_fire_increase_speed;

    /** \brief Number of ice's units loss in the ice environment
     * during one second. */
    static const double s_ice_loss_speed;

    /** \brief Number of ice's units won in the ice environment
     * during one second. */
    static const double s_ice_increase_speed;

    /** \brief The maximum halo height. */
    static const bear::universe::size_type s_max_halo_height;

    /** \brief The maximum halo hand width. */
    static const bear::universe::size_type s_max_halo_hand_width;

    /** \brief  The time to crouch. */
    static const bear::universe::time_type s_time_to_crouch;

    /** \brief  The time to look_upward. */
    static const bear::universe::time_type s_time_to_look_upward;

    /** \brief The time after which Player is waiting. */
    static const bear::universe::time_type s_time_to_wait;

    /** \brief The time over which Player jump automatically. */
    static const bear::universe::time_type s_time_to_jump;

    /** \brief The time over which Player throw automatically. */
    static const bear::universe::time_type s_time_to_start_throw;

    /** \brief The time over which Player cannot cling. */
    static const bear::universe::time_type s_max_time_to_cling;

    /** \brief The time over which Player cannot hang. */
    static const bear::universe::time_type s_max_time_to_hang;

    /** \brief The time over which Player cannot float in air. */
    static const bear::universe::time_type s_max_time_air_float;

    /** \brief How long do we allow to add a force when jumping */
    static const bear::universe::time_type s_max_time_continue_jump;

  }; // class player
} // namespace ptb

#endif // __PTB_PLAYER_HPP__
