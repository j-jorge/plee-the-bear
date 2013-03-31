/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::player class.
 * \author Sebastien Angibaud
 */
#include "ptb/player.hpp"
#include <sstream>

#include "engine/game.hpp"
#include "engine/level.hpp"
#include "engine/world.hpp"
#include "engine/message/transition_effect_message.hpp"
#include "engine/message/transition_effect_erase_message.hpp"

#include "generic_items/tweener_item.hpp"
#include "generic_items/camera_shaker.hpp"
#include "generic_items/decorative_effect.hpp"
#include "generic_items/star.hpp"

#include "universe/forced_movement/forced_tracking.hpp"

#include "ptb/defines.hpp"
#include "ptb/gauge.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/item_brick/monster.hpp"
#include "ptb/item_brick/sniffable.hpp"
#include "ptb/player_action.hpp"
#include "ptb/player_signals.hpp"
#include "ptb/throwable_item/air_honeypot_throwable_item.hpp"
#include "ptb/throwable_item/corrupting_item_throwable_item.hpp"
#include "ptb/throwable_item/fire_honeypot_throwable_item.hpp"
#include "ptb/throwable_item/hazelnut_throwable_item.hpp"
#include "ptb/throwable_item/stone_throwable_item.hpp"
#include "ptb/throwable_item/water_honeypot_throwable_item.hpp"

#include "ptb/item/air_bubble.hpp"
#include "ptb/item/floating_score.hpp"
#include "ptb/item/power_effect.hpp"
#include "ptb/item/shared_camera.hpp"
#include "ptb/item/small_honeypot.hpp"
#include "ptb/item/stone/air_fire_stone.hpp"
#include "ptb/item/stone/air_fire_water_stone.hpp"
#include "ptb/item/stone/air_water_stone.hpp"
#include "ptb/item/stone/air_stone.hpp"
#include "ptb/item/stone/water_fire_stone.hpp"
#include "ptb/item/stone/water_stone.hpp"
#include "ptb/item/stone/fire_stone.hpp"
#include "ptb/item/hazelnut.hpp"
#include "ptb/item/corrupting_bonus_attractor.hpp"
#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/player_state/state_player.hpp"
#include "ptb/player_state/state_roar.hpp"
#include "ptb/player_state/state_walk.hpp"
#include "ptb/player_state/state_idle.hpp"
#include "ptb/player_state/state_jump.hpp"
#include "ptb/player_state/state_fall.hpp"
#include "ptb/player_state/state_dead.hpp"
#include "ptb/player_state/state_game_over.hpp"
#include "ptb/player_state/state_run.hpp"
#include "ptb/player_state/state_slap.hpp"
#include "ptb/player_state/state_start_jump.hpp"
#include "ptb/player_state/state_vertical_jump.hpp"
#include "ptb/player_state/state_look_upward.hpp"
#include "ptb/player_state/state_crouch.hpp"
#include "ptb/player_state/state_captive.hpp"
#include "ptb/player_state/state_throw.hpp"
#include "ptb/player_state/state_maintain.hpp"
#include "ptb/player_state/state_wait.hpp"
#include "ptb/player_state/state_start_cling.hpp"
#include "ptb/player_state/state_cling.hpp"
#include "ptb/player_state/state_clung_jump.hpp"
#include "ptb/player_state/state_start_hang.hpp"
#include "ptb/player_state/state_hang.hpp"
#include "ptb/player_state/state_sink.hpp"
#include "ptb/player_state/state_swimming.hpp"
#include "ptb/player_state/state_float.hpp"
#include "ptb/player_state/state_injured.hpp"
#include "ptb/player_state/state_paralyze.hpp"

#include "ptb/transition_effect/game_over_effect.hpp"
#include "ptb/transition_effect/invincibility_effect.hpp"

#include "ptb/util/player_util.hpp"

#include <claw/tween/easing/easing_linear.hpp>

/*----------------------------------------------------------------------------*/
const double ptb::player::s_max_oxygen_gauge = 10000;
const double ptb::player::s_max_heat_gauge = 10000;
const double ptb::player::s_max_cold_gauge = 10000;

const double ptb::player::s_oxygen_loss_speed = 200;
const double ptb::player::s_oxygen_inspiration_speed = 1500;
const double ptb::player::s_fire_loss_speed = 200;
const double ptb::player::s_fire_increase_speed = 1500;
const double ptb::player::s_ice_loss_speed = 200;
const double ptb::player::s_ice_increase_speed = 1500;

const bear::universe::size_type ptb::player::s_max_halo_height = 64;
const bear::universe::size_type ptb::player::s_max_halo_hand_width = 35;

const bear::universe::time_type ptb::player::s_time_to_crouch = 0.5;
const bear::universe::time_type ptb::player::s_time_to_look_upward = 0.5;
const bear::universe::time_type ptb::player::s_time_to_wait = 3;
const bear::universe::time_type ptb::player::s_time_to_jump = 1;
const bear::universe::time_type ptb::player::s_time_to_run = 1.2;
const bear::universe::time_type ptb::player::s_time_to_start_throw = 0.34;
const bear::universe::time_type ptb::player::s_max_time_to_cling = 0.3;
const bear::universe::time_type ptb::player::s_max_time_to_hang = 1;
const bear::universe::time_type ptb::player::s_max_time_air_float = 1;
const bear::universe::time_type ptb::player::s_max_time_continue_jump = 0.26;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player::player()
  : m_current_state(roar_state), m_last_visual_time(0),
    m_oxygen_gauge(s_max_oxygen_gauge), m_cold_gauge(s_max_cold_gauge),
    m_heat_gauge(s_max_heat_gauge), m_status_look_upward(false),
    m_status_crouch(false), m_can_cling(false),
    m_cling_orientation(false), m_halo_animation(NULL),
    m_halo_hand_animation(NULL), m_move_right(false), m_move_left(false),
    m_move_force(0), m_index(0), m_nb_bottom_contact(0),
    m_controller_number(0),
    m_air_float(false), m_injured_orientation(true),
    m_hot_spot_position(0, 0),
    m_hot_spot_minimum(0, 0), m_hot_spot_maximum(0, 0),
    m_hot_spot_balance_move(0, 0), m_corrupting_bonus_attractor(NULL)
{
  init();

  m_offensive_force = 10;
  m_energy = 100;
  m_offensive_phase = false;
  m_offensive_coefficients[normal_attack] = 1;
} // player::player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player::player( const player& p )
  : super(p),
    m_current_state(p.roar_state), m_last_visual_time(0),
    m_oxygen_gauge(s_max_oxygen_gauge), m_cold_gauge(s_max_cold_gauge),
    m_heat_gauge(s_max_heat_gauge),
    m_status_look_upward(p. m_status_look_upward),
    m_status_crouch(p.m_status_crouch), m_can_cling(p. m_can_cling),
    m_cling_orientation(p.m_cling_orientation),
    m_halo_animation(NULL), m_halo_hand_animation(NULL),
    m_move_right(p. m_move_right), m_move_left(p.m_move_left), m_move_force(0),
    m_index(0), m_nb_bottom_contact(0), m_controller_number(0),
    m_injured_orientation(true),
    m_hot_spot_position(0, 0),
    m_hot_spot_minimum(0, 0), m_hot_spot_maximum(0, 0),
    m_hot_spot_balance_move(0, 0), m_corrupting_bonus_attractor(NULL)
{
  init();

  set_index(p.get_index());

  if ( m_defensive_powers[monster::air_attack] )
    game_variables::set_air_power(get_index(), true);

  if ( m_defensive_powers[monster::fire_attack] )
    game_variables::set_fire_power(get_index(), true);

  if ( m_defensive_powers[monster::water_attack] )
    game_variables::set_water_power(get_index(), true);
} // player::player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Init member variables.
 */
void ptb::player::init()
{
  set_z_fixed(false);
  set_weak_collisions(false);
  m_offensive_phase = false;

  set_spot_minimum(-200, -250);
  set_spot_maximum(200, 220);
  set_spot_balance_move(3, 15);
  set_air_float(false);

  save_current_position();
  m_last_bottom_left = bear::universe::position_type(0, 0);
  m_monster_type = monster::player_monster;

  m_invincible_time = 0;
  m_run_time = 0;

  m_states.resize(27);
  m_states[walk_state] = new state_walk(this);
  m_states[idle_state] = new state_idle(this);
  m_states[jump_state] = new state_jump(this);
  m_states[fall_state] = new state_fall(this);
  m_states[dead_state] = new state_dead(this);
  m_states[game_over_state] = new state_game_over(this);
  m_states[roar_state] = new state_roar(this);
  m_states[run_state] = new state_run(this);
  m_states[slap_state] = new state_slap(this);
  m_states[start_jump_state] = new state_start_jump(this);
  m_states[vertical_jump_state] = new state_vertical_jump(this);
  m_states[look_upward_state] = new state_look_upward(this);
  m_states[crouch_state] = new state_crouch(this);
  m_states[captive_state] = new state_captive(this);
  m_states[throw_state] = new state_throw(this);
  m_states[wait_state] = new state_wait(this);
  m_states[start_cling_state] = new state_start_cling(this);
  m_states[cling_state] = new state_cling(this);
  m_states[clung_jump_state] = new state_clung_jump(this);
  m_states[start_hang_state] = new state_start_hang(this);
  m_states[hang_state] = new state_hang(this);
  m_states[swimming_state] = new state_swimming(this);
  m_states[sink_state] = new state_sink(this);
  m_states[float_state] = new state_float(this);
  m_states[maintain_state] = new state_maintain(this);
  m_states[injured_state] = new state_injured(this);
  m_states[paralyze_state] = new state_paralyze(this);

  m_progress = &player::progress_roar;
} // player::init()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::player::~player()
{
  unsigned int i;

  for (i=0; i!=m_states.size(); ++i)
    delete m_states[i];

  if ( m_halo_animation )
    delete m_halo_animation;

  if ( m_halo_hand_animation )
    delete m_halo_hand_animation;
} // player::~player()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress( bear::universe::time_type elapsed_time )
{
  // THIS CONDITION MUST BE CHECKED FIRST
  if ( !is_a_marionette() )
    progress_input_actions(elapsed_time);
  else
    dummy_progress_input_actions(elapsed_time);

  super::progress(elapsed_time);

  m_state_time += elapsed_time;
  m_run_time += elapsed_time;
  m_jump_time += elapsed_time;

  progress_corrupting_bonus_attractor(elapsed_time);

  if ( m_air_float )
    progress_air_float(elapsed_time);

  m_jump_force = get_mass() * 7500 *
    (1 - (m_jump_time / s_max_time_continue_jump)
     * (m_jump_time / s_max_time_continue_jump) );

  if (m_jump_force <= 0)
    m_jump_force = 0;

  progress_invincibility(elapsed_time);
  m_throwable_items.progress(elapsed_time);

  if ( is_crushed() && (m_current_state != player::dead_state) )
    apply_die();
  else
    {
      if ( m_progress != NULL )
        (this->*m_progress)(elapsed_time);

      if ( is_only_in_environment(bear::universe::water_environment) )
        progress_in_water(elapsed_time);

      update_powers();
      progress_spot( elapsed_time );
      progress_gauges( elapsed_time );
      update_orientation();
      m_can_cling = false;

      if ( ( m_current_state == player::maintain_state ) ||
           ( m_current_state == player::throw_state ) )
        m_halo_hand_animation->next(elapsed_time);

      m_animation_to_throw.next(elapsed_time);
    }

  m_last_bottom_left = get_bottom_left();
  m_can_throw_power[air_attack] = true;
  m_can_throw_power[fire_attack] = true;
  m_can_throw_power[water_attack] = true;
  if ( m_throwable_items.get_current_throwable_item()->is_empty() )
    m_throwable_items.next();
} // player::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void
ptb::player::get_visual( std::list<bear::engine::scene_visual>& visuals ) const
{
  get_visuals_without_invincibility(visuals);

  std::list< std::list<bear::engine::scene_visual> >::const_iterator it;

  for ( it = m_last_visuals.begin(); it != m_last_visuals.end(); ++it )
    {
      std::list<bear::engine::scene_visual>::const_iterator it2;
      for (it2 = it->begin(); it2 != it->end(); ++it2 )
        visuals.push_front(*it2);
    }
} // player::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::player::pre_cache()
{
  super::pre_cache();

  // halo for vertical jump
  get_level_globals().load_animation("animation/plee/halo.canim");
  get_level_globals().load_animation("animation/plee/halo_hand.canim");

  // small honeypot
  get_level_globals().load_animation("animation/powerup/small_fire.canim");
  get_level_globals().load_animation("animation/powerup/small_air.canim");
  get_level_globals().load_animation("animation/powerup/small_water.canim");

  // stones
  get_level_globals().load_model("model/stones/stone.cm");
  get_level_globals().load_model("model/stones/air_stone.cm");
  get_level_globals().load_model("model/stones/water_stone.cm");
  get_level_globals().load_model("model/stones/fire_stone.cm");
  get_level_globals().load_model("model/stones/air_fire_stone.cm");
  get_level_globals().load_model("model/stones/air_water_stone.cm");
  get_level_globals().load_model("model/stones/water_fire_stone.cm");
  get_level_globals().load_model("model/stones/air_fire_water_stone.cm");
  get_level_globals().load_animation("animation/stones/sliver_1.canim");
  get_level_globals().load_animation("animation/stones/sliver_2.canim");
  get_level_globals().load_animation("animation/stones/sliver_3.canim");
  get_level_globals().load_animation("animation/stones/sliver_4.canim");
  get_level_globals().load_animation("animation/stones/sliver_5.canim");
  get_level_globals().load_animation("animation/steam.canim");

  // musics
  get_level_globals().load_sound("music/1-up.ogg");
  get_level_globals().load_sound("music/game-over.ogg");
  get_level_globals().load_sound("music/invincibility.ogg");

  // sounds
  get_level_globals().load_sound("sound/grr.wav");
  get_level_globals().load_sound("sound/plee/snore.ogg");
} // player::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void ptb::player::on_enters_layer()
{
  super::on_enters_layer();

  if ( m_defensive_powers[monster::air_attack] )
    game_variables::set_air_power(get_index(), true);

  if ( m_defensive_powers[monster::fire_attack] )
    game_variables::set_fire_power(get_index(), true);

  if ( m_defensive_powers[monster::water_attack] )
    game_variables::set_water_power(get_index(), true);

  m_authorized_action.resize(player_action::max_value + 1);
  for ( unsigned int i=0; i <= player_action::max_value; ++i)
    m_authorized_action[i] = true;

  m_energy = game_variables::get_max_energy(m_index);
  set_air_float(false);
  m_injured_orientation = true;

  fill_throwable_items();
  save_current_position();

  m_wait_state_number = 0;
  m_want_clung_jump = false;
  bear::engine::level_globals& glob = get_level_globals();

  m_halo_animation = new bear::visual::animation
    ( glob.get_animation("animation/plee/halo.canim") );

  m_halo_hand_animation = new bear::visual::animation
    ( glob.get_animation("animation/plee/halo_hand.canim") );

  if ( ( m_index == 1 ) || ( m_index == 2 ) )
    get_level().add_interest_around(this);

  m_can_throw_power[air_attack] = true;
  m_can_throw_power[fire_attack] = true;
  m_can_throw_power[water_attack] = true;

  create_power_effect();
} // player::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::player::is_valid() const
{
  return (m_index != 0) && super::is_valid();
} // player::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type unsigned integer.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::player::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if (name == "player.index")
    set_index(value);
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // player::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the position of the player.
 * \param p The center of mass to remember.
 */
void ptb::player::save_position( const bear::universe::position_type& p )
{
  m_saved_position = p;
} // player::save_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the current position of the player.
 */
void ptb::player::save_current_position()
{
  save_position( get_center_of_mass() );
} // player::save_current_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell to Player to start an action.
 * \param a The action to start.
 */
void ptb::player::start_action( player_action::value_type a )
{
  if ( m_authorized_action[a] )
    switch( a )
      {
      case player_action::idle : break;
      case player_action::move_left : break;
      case player_action::move_right : break;
      case player_action::jump :
        m_states[m_current_state]->do_jump(); break;
      case player_action::get_camera : do_get_camera(); break;
      case player_action::slap :
        m_states[m_current_state]->do_slap(); break;
      case player_action::look_upward : do_start_look_upward(); break;
      case player_action::crouch : do_start_crouch(); break;
      case player_action::change_object :
        m_states[m_current_state]->do_start_change_object(); break;
      case player_action::captive : break;
      case player_action::release : break;
      case player_action::throw_stone : do_start_throw(); break;
      case player_action::die : apply_die(); break;
      case player_action::roar : start_action_model("roar"); break;
      case player_action::disappear : start_action_model("disappear"); break;
      case player_action::action_null: break;
      default:
        claw::logger << claw::log_warning << "Action ignored (start): " << a
                     << std::endl;;
      }
} // player::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell to the player to do an action.
 * \param elapsed_time How long the action is done.
 * \param a The action to do.
 */
void ptb::player::do_action
( bear::universe::time_type elapsed_time, player_action::value_type a )
{
  switch( a )
      {
      case player_action::move_left :
        if ( !get_rendering_attributes().is_mirrored() )
          m_injured_orientation = true;
        m_states[m_current_state]->do_move_left(); break;
      case player_action::move_right :
        if ( get_rendering_attributes().is_mirrored() )
          m_injured_orientation = true;
        m_states[m_current_state]->do_move_right(); break;

      default:

        if ( m_authorized_action[a] )
          switch( a )
            {
            case player_action::idle : choose_idle_state(); break;
            case player_action::jump :
              m_states[m_current_state]->do_continue_jump(); break;
            case player_action::get_camera : break;
            case player_action::slap : break;
            case player_action::look_upward :
              m_states[m_current_state]->do_continue_look_upward(); break;
            case player_action::crouch :
              m_states[m_current_state]->do_continue_crouch(); break;
            case player_action::change_object : break;
            case player_action::captive :
              m_states[m_current_state]->captive(); break;
            case player_action::release :
              m_states[m_current_state]->release(); break;
            case player_action::throw_stone : break;
            case player_action::die : break;
            case player_action::action_null: break;
            default:
              claw::logger << claw::log_warning << "Action ignored: " << a
                           << std::endl;
            }
      }
} // player::do_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell to player to stop an action.
 * \param a The action to stop.
 */
void ptb::player::stop_action( player_action::value_type a )
{
  if ( m_authorized_action[a] )
    switch( a )
      {
      case player_action::idle : break;
      case player_action::move_left :
        m_want_clung_jump = false; break;
      case player_action::move_right :
        m_want_clung_jump = false; break;
      case player_action::jump :
        m_states[m_current_state]->do_stop_vertical_jump(); break;
      case player_action::get_camera : break;
      case player_action::slap : break;
      case player_action::look_upward : do_stop_look_upward(); break;
      case player_action::crouch :
        do_stop_crouch(); break;
      case player_action::throw_stone :
        m_states[m_current_state]->do_stop_throw(); break;
      case player_action::change_object : break;
      case player_action::captive : break;
      case player_action::release : break;
      case player_action::die : break;
      case player_action::action_null: break;
      default:
        claw::logger << claw::log_warning << "Action ignored (stop): " << a
                     << std::endl;
      }
} // player::stop_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start a new action of model.
 * \param action The action to start.
 */
void ptb::player::start_action_model(const std::string& action)
{
  start_model_action(action);
} // player::start_action_model()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given action is authorized.
 * \param a Tha action to set.
 * \param value The new state of the action (true if authorized).
*/
void ptb::player::set_authorized_action(player_action::value_type a, bool value)
{
  m_authorized_action[a] = value;
} // player::set_authorized_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Authorize a given action.
 * \param a The name of the action to authorize.
 */
void ptb::player::authorize_action( const std::string& a )
{
  const player_action::value_type c = player_action::from_string(a);

  if ( c != player_action::action_null )
    m_authorized_action[c] = true;
} // player::authorize_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Authorize all the actions.
 */
void ptb::player::authorize_all_actions()
{
  for ( std::size_t i=0; i!=m_authorized_action.size(); ++i )
    m_authorized_action[i] = true;
} // player::authorize_all_actions()

/*----------------------------------------------------------------------------*/
/**
 * \brief Disable all the actions.
 */
void ptb::player::disable_all_actions()
{
  for ( std::size_t i=0; i!=m_authorized_action.size(); ++i )
    m_authorized_action[i] = false;
} // player::disable_all_actions()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the gauge of the oxygen.
 */
const ptb::gauge& ptb::player::get_oxygen_gauge() const
{
  return m_oxygen_gauge;
} // player::get_oxygen_gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the gauge of the cold.
 */
const ptb::gauge& ptb::player::get_cold_gauge() const
{
  return m_cold_gauge;
} // player::get_cold_gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the gauge of the heat.
 */
const ptb::gauge& ptb::player::get_heat_gauge() const
{
  return m_heat_gauge;
} // player::get_heat_gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get player's signals.
 */
ptb::player_signals& ptb::player::get_signals()
{
  return m_signals;
} // player::get_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the ratio of the length of preparation of the jump.
 */
bear::universe::time_type ptb::player::get_jump_time_ratio() const
{
  return m_jump_time_ratio;
} // player::get_jump_time_ratio()

/*----------------------------------------------------------------------------*/
/**
 * \brief Updtae the ratio of the preparation of throw state.
 */
void ptb::player::update_throw_time_ratio()
{
  m_throw_time_ratio = m_state_time / s_time_to_start_throw;
} // player::update_throw_time_ratio()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of throw_down.
 * \param value The state of throw_down.
 */
void ptb::player::set_throw_down(bool value)
{
  m_throw_down = value;
} // player::set_throw_down()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to throw an hazelnut
 */
void ptb::player::throw_hazelnut()
{
  m_throwable_items.select(hazelnut_throwable_item::s_name);

  start_action(player_action::throw_stone);
  apply_maintain();
  m_state_time = 0.01;
  stop_action(player_action::throw_stone);

  set_state(player::maintain_state);
} // player::throw_hazelnut()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the set of throwable_items.
 */
const ptb::throwable_items_container& ptb::player::get_throwable_items() const
{
  return m_throwable_items;
} // player::get_throwable_items()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the set of throwable_items.
 */
ptb::throwable_items_container& ptb::player::get_throwable_items()
{
  return m_throwable_items;
} // player::get_throwable_items()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of throw_up.
 * \param value The state of throw_up.
 */
void ptb::player::set_throw_up(bool value)
{
  m_throw_up = value;
} // player::set_throw_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Player is a marionette.
 */
bool ptb::player::is_a_marionette() const
{
  return (m_controller_number != 0);
} // player::is_a_marionette()

/*----------------------------------------------------------------------------*/
/**
 * \brief Turn on/off the marionette state of Player.
 * \param b The new value of the state.
 */
void ptb::player::set_marionette( bool b )
{
  if ( b )
    ++m_controller_number;
  else
    {
      CLAW_PRECOND( m_controller_number >= 1 );
      --m_controller_number;
    }
} // player::set_marionette()

/*----------------------------------------------------------------------------*/
/**
 * \brief Turn on/off the air_float status of Player.
 * \param b The new value of the state.
 */
void ptb::player::set_air_float( bool b )
{
  m_air_float = b;
  m_air_float_time = 0;
} // player::set_air_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the look up status.
 */
void ptb::player::set_status_look_upward(bool status)
{
  m_status_look_upward = status;
} // player::set_status_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the look up status.
 */
bool ptb::player::get_status_look_upward() const
{
  return m_status_look_upward;
} // player::get_status_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the crouch status.
 */
void ptb::player::set_status_crouch(bool status)
{
  m_status_crouch = status;
} // player::set_status_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the crouch status.
 */
bool ptb::player::get_status_crouch() const
{
  return m_status_crouch;
} // player::get_status_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player start to look up.
 */
void ptb::player::do_start_look_upward()
{
  m_status_look_upward = true;
  m_look_upward_time = 0;
  m_states[m_current_state]->do_look_upward();
} // player::do_start_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player start to crouch.
 */
void ptb::player::do_start_crouch()
{
  m_status_crouch = true;
  m_crouch_time = 0;
  m_states[m_current_state]->do_crouch();
} // player::do_start_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player start to throw.
 */
void ptb::player::do_start_throw()
{
  if ( m_throwable_items.get_current_throwable_item()->can_throw()
       && m_air_stones.empty() )
    {
      m_animation_to_throw =
        get_level_globals().get_animation
        ( m_throwable_items.get_current_throwable_item()->get_animation() );

      m_states[m_current_state]->do_start_throw();
    }
  else if ( ! m_air_stones.empty() )
    apply_blast_stone();
  else
    m_throwable_items.throwable_item_no_stock();
} // player::do_start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if Player can cling.
 * \param status The new status.
 */
void ptb::player::set_can_cling(bool status)
{
  m_can_cling = status;
} // player::set_can_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the player is clung.
 */
bool ptb::player::is_clung() const
{
  return ( m_current_state == cling_state );
} // player::is_clung()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if Player want to do a clumb jump.
 * \param status The new status.
 */
void ptb::player::set_want_clung_jump(bool status)
{
  m_want_clung_jump = status;
} // player::set_want_clung_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the player want to do a clung jump.
 */
bool ptb::player::want_clung_jump() const
{
  return m_want_clung_jump;
} // player::want_clung_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player receives energy.
 *
 * \param energy The energy received.
 */
void ptb::player::receive_energy(double energy)
{
  bool signal( ( m_energy < game_variables::get_max_energy(m_index) ) &&
               ( energy != 0 ) );

  m_energy += energy;

  if ( m_energy > game_variables::get_max_energy(m_index) )
    m_energy = game_variables::get_max_energy(m_index);

  if ( signal )
    m_signals.energy_added(m_energy);

  create_soul_decoration();
} // player::receive_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief We remove some energy of the item..
 *
 * \param attacker The attacker monster.
 * \param energy The quantity of energy removed.
 */
void ptb::player::remove_energy(const monster& attacker, double energy )
{
  double last_energy(m_energy);
  super::remove_energy(attacker, energy);

  if ( m_energy != last_energy )
    m_signals.energy_removed(m_energy);
} // player::remove_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::player::has_attacked(const monster& other)
{
  super::has_attacked(other);

  if ( ( other.get_monster_type() == monster::player_monster ) &&
       ( ! level_variables::get_friendly_fire( get_level() ) ) )
    {
      status_layer_notification_message msg;
      
      bear::visual::sprite sp;
      msg.set_notification
	( get_monster_index(), sp, gettext("snake in the grass"));
      
      get_level_globals().send_message
	( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
    }
} // player::has_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the invincible status.
 * \param invincible The new invincible status.
 */
void ptb::player::set_invincible(const bool invincible)
{
  super::set_invincible(invincible);

  if ( m_invincible )
    {
      m_invincible_time = 0;
      m_last_visual_time = 0;
      m_last_visuals.clear();

      bear::engine::transition_effect_message<invincibility_effect> msg(-1000);

      get_level_globals().send_message
        ( PTB_TRANSITION_EFFECT_DEFAULT_TARGET_NAME, msg );
      m_invincible_id_effect = msg.get_id();
    }
} // player::set_invincible()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player receives oxygen.
 *
 * \param oxygen The oxygen received.
 */
void ptb::player::receive_oxygen(double oxygen)
{
  m_oxygen_gauge.add_value(oxygen);
  m_signals.oxygen_gauge_changed(m_oxygen_gauge.get_value());
} // player::receive_oxygen()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player receives a one up.
 *
 */
void ptb::player::give_one_up()
{
  floating_score* s = new floating_score;

  new_item(*s);

  s->set_center_of_mass( get_center_of_mass() );
  s->set_z_position( std::numeric_limits<int>::max() );
  s->one_up(get_index());
} // player::give_one_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a air_stone in the air stone set.
 *
 * \param s The stone to add.
 */
void ptb::player::add_air_stone(ptb::stone* s)
{
  m_air_stones.insert(s);
} // player::add_air_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a air_stone in the air stone set.
 *
 * \param s The stone to remove.
 */
void ptb::player::remove_air_stone( ptb::stone* s)
{
  std::set< ptb::stone* >::iterator it;
  it = m_air_stones.find(s);

  if ( it != m_air_stones.end() )
    m_air_stones.erase(it);
} // player::remove_air_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Player can throw a given power.
 * \param b The status.
 * \param a The corresponding attack
 */
void ptb::player::set_can_throw_power( bool b, monster::attack_type a)
{
  m_can_throw_power[a] = b;
} // player::set_can_throw_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if Player can throw a given power.
 * \param a The corresponding attack
 */
bool ptb::player::can_throw_power(const monster::attack_type a) const
{
  bool result = false;

  std::map<monster::attack_type, bool>::const_iterator it =
    m_can_throw_power.find(a);

  if ( it !=  m_can_throw_power.end() )
    result = it->second;

  return result;
} // player::can_throw_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the coordinates of the point to target to (for camera or active
 *        region).
 */
bear::universe::position_type ptb::player::hot_spot() const
{
  bear::universe::position_type p;

  bear::universe::size_type w, h;
  get_action("idle")->get_max_size(w, h);
  const bear::universe::size_box_type half_player( w / 2, h / 2 );

  if ( get_rendering_attributes().is_mirrored() )
    {
      p = get_bottom_right();
      p.x -= half_player.x;
    }
  else
    {
      p = get_bottom_left();
      p.x += half_player.x;
    }

  p.y += half_player.y;

  return p + m_hot_spot_position;
} // player::hot_spot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the index of this player.
 */
unsigned int ptb::player::get_index() const
{
  return m_index;
} // player::get_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the index of this player.
 * \param index The index of the player.
 */
void ptb::player::set_index( unsigned int index )
{
  m_index = index;
  set_name( util::get_player_name(index) );
  set_player_index(index);
  m_monster_index = index;
} // player::set_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the minimum acceptable value for the position of the hot spot.
 * \param x Minimum value on the X-axis.
 * \param y Minimum value on the Y-axis.
 */
void ptb::player::set_spot_minimum
( bear::universe::coordinate_type x, bear::universe::coordinate_type y )
{
  m_hot_spot_minimum.set
    ( std::min(x, m_hot_spot_maximum.x), std::min(y, m_hot_spot_maximum.y) );
} // player::set_spot_minimum()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the maximum acceptable value for the position of the hot spot.
 * \param x Maximum value on the X-axis.
 * \param y Maximum value on the Y-axis.
 */
void ptb::player::set_spot_maximum
( bear::universe::coordinate_type x, bear::universe::coordinate_type y )
{
  m_hot_spot_maximum.set
    ( std::max(x, m_hot_spot_minimum.x), std::max(y, m_hot_spot_minimum.y) );
} // player::set_spot_maximum()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the maximum movement allowed when balancing the hot spot.
 * \param x Maximum movement on the X-axis.
 * \param y Maximum movement on the Y-axis.
 */
void ptb::player::set_spot_balance_move
( bear::universe::coordinate_type x, bear::universe::coordinate_type y )
{
  m_hot_spot_balance_move.set(std::abs(x), std::abs(y));
} // player::set_spot_balance_move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Change the gap of the spot.
 * \param gap The vector of gap.
 */
void ptb::player::add_spot_gap( const bear::universe::position_type& gap )
{
  m_hot_spot_position += gap;

  if ( m_hot_spot_position.x > m_hot_spot_maximum.x )
    m_hot_spot_position.x -= std::abs(gap.x);
  else if ( m_hot_spot_position.x < m_hot_spot_minimum.x )
    m_hot_spot_position.x += std::abs(gap.x);

  if ( m_hot_spot_position.y > m_hot_spot_maximum.y )
    m_hot_spot_position.y -= std::abs(gap.y);
  else if ( m_hot_spot_position.y < m_hot_spot_minimum.y )
    m_hot_spot_position.y += std::abs(gap.y);
} // player::add_spot_gap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Balance the gap of the spot.
 * \param x Tell if we balance on the X-axis.
 * \param y Tell if we balance on the Y-axis.
 */
void ptb::player::balance_spot(bool x, bool y)
{
  if ( x )
    {
      if ( m_hot_spot_position.x > m_hot_spot_balance_move.x )
        m_hot_spot_position.x -= m_hot_spot_balance_move.x;
      else if ( m_hot_spot_position.x < -m_hot_spot_balance_move.x)
        m_hot_spot_position.x += m_hot_spot_balance_move.x;
      else
        m_hot_spot_position.x = 0;
    }

  if ( y )
    {
      if ( m_hot_spot_position.y > m_hot_spot_balance_move.y )
        m_hot_spot_position.y -= m_hot_spot_balance_move.y;
      else if ( m_hot_spot_position.y < -m_hot_spot_balance_move.y)
        m_hot_spot_position.y += m_hot_spot_balance_move.y;
      else
        m_hot_spot_position.y = 0;
    }
} // player::balance_spot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Change the current throwable_item.
 */
void ptb::player::apply_change_object()
{
  if ( m_throwable_items.has_next() )
    m_throwable_items.next();
  else
    m_throwable_items.throwable_item_no_stock();
} // player::apply_change_object()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action move_right.
 */
void ptb::player::apply_move_right()
{
  if ( m_authorized_action[player_action::move_right]  )
    {
      m_move_right = true;
      add_internal_force( bear::universe::force_type(m_move_force, 0) );
    }
  if ( get_speed().x == 0 )
    get_rendering_attributes().mirror(false);
} // player::apply_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action move_left.
 */
void ptb::player::apply_move_left()
{
  if ( m_authorized_action[player_action::move_left]  )
    {
      m_move_left = true;
      add_internal_force( bear::universe::force_type(-m_move_force, 0) );
    }
  else if ( get_speed().x == 0 )
    get_rendering_attributes().mirror(true);
} // player::apply_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply impulsion of a jump.
 */
void ptb::player::apply_impulse_jump()
{
  if ( m_current_state == float_state )
    {
      add_internal_force
        ( bear::universe::force_type(0, get_jump_force_in_float()) );
      start_action_model("jump");
    }
  else
    {
      m_jump_time = 0;
      add_external_force( bear::universe::force_type(0, 2*get_jump_force() ) );
    }
} // player::apply_impulse_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action jump.
 */
void ptb::player::apply_jump()
{
  m_move_force = get_move_force_in_jump();
  set_state(player::jump_state);
  m_progress = &player::progress_jump;
} // player::apply_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action continue_jump.
 */
void ptb::player::apply_continue_jump()
{
  if ( m_jump_time <= s_max_time_continue_jump )
    add_external_force( bear::universe::force_type(0, m_jump_force) );
} // player::apply_continue_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action start_jump.
 */
void ptb::player::apply_start_jump()
{
  set_state(player::start_jump_state);
  m_progress = &player::progress_start_jump;
  m_halo_animation->reset();
} // player::apply_start_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action vertical_jump.
 *
 */
void ptb::player::apply_vertical_jump()
{
  m_move_force = get_move_force_in_vertical_jump();
  m_run_time = 0;

  if ( m_state_time >= s_time_to_jump )
    m_jump_time_ratio = 1;
  else
    m_jump_time_ratio = m_state_time / s_time_to_jump;

  set_state(player::vertical_jump_state);
  m_progress = &player::progress_vertical_jump;
} // player::apply_vertical_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action fall.
 *
 */
void ptb::player::apply_fall()
{
  m_move_force = get_move_force_in_jump();
  set_state(player::fall_state);
  m_progress = &player::progress_fall;
} // player::apply_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action idle.
 *
 */
void ptb::player::apply_idle()
{
  m_move_force = get_move_force_in_idle();
  set_state(player::idle_state);
  m_progress = &player::progress_idle;
} // player::apply_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action walk.
 *
 */
void ptb::player::apply_walk()
{
  m_move_force = get_move_force_in_idle();
  set_state(player::walk_state);
  m_progress = &player::progress_walk;
} // player::apply_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action run.
 */
void ptb::player::apply_run()
{
  m_move_force = get_move_force_in_run();
  set_state(player::run_state);
  m_progress = &player::progress_run;
} // player::apply_run()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action slap.
 */
void ptb::player::apply_slap()
{
  m_move_force = get_move_force_in_idle();
  set_state(player::slap_state);
  m_progress = &player::progress_slap;
  apply_attack();
} // player::apply_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Turn the attack mode.
 */
void ptb::player::apply_attack()
{
  set_offensive_phase(true);
  set_defensive_power(monster::normal_attack, true);
} // player::apply_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action captive.
 *
 */
void ptb::player::apply_captive()
{
  set_state(player::captive_state);
  m_progress = &player::progress_captive;
} // player::apply_captive()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop the action captive.
 *
 */
void ptb::player::apply_release()
{
  choose_idle_state();
  m_progress = &player::progress_idle;
} // player::apply_release()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action throw.
 *
 */
void ptb::player::apply_throw()
{
  if ( get_current_action_name() == "throw_and_fall" )
    m_move_force = get_move_force_in_jump();
  else
    m_move_force = get_move_force_in_idle();

  set_state(player::throw_state);
  m_progress = &player::progress_throw;
} // player::apply_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action maintain.
 *
 */
void ptb::player::apply_maintain()
{
  if ( get_current_action_name() == "maintain_and_fall" )
    m_move_force = get_move_force_in_jump();
  else
    m_move_force = get_move_force_in_idle();

  m_throw_time_ratio = 0;
  set_state(player::maintain_state);
  m_progress = &player::progress_maintain;
} // player::apply_maintain()

/*----------------------------------------------------------------------------*/
/**
 * \brief Throw an object.
 */
void ptb::player::apply_throw_object()
{
  if ( m_throw_time_ratio == 0 )
    m_throw_time_ratio = 1;

  if ( m_throwable_items.get_current_throwable_item()->can_throw() )
    {
      bear::engine::base_item* item =
        m_throwable_items.get_current_throwable_item()
        ->create_throwable_item();

      if ( item )
        {
          m_throwable_items.get_current_throwable_item()->decrease_stock();
          m_throwable_items.control_current_throwable_item();

          bear::engine::model_mark_placement m;
          if ( get_mark_placement("hand", m) )
            item->set_center_of_mass(m.get_position());
          else
            item->set_center_of_mass(get_center_of_mass());

          item->set_z_position(get_z_position() + 2);
          item->add_external_force(get_object_force()*item->get_mass());

          new_item( *item );
        }
    }

  m_animation_to_throw = bear::visual::animation();
} // player::apply_throw_object()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action blast_stone.
 *
 */
void ptb::player::apply_blast_stone()
{
  std::set<ptb::stone*> save_stones(m_air_stones);
  std::set<ptb::stone*>::iterator it;
  for ( it = save_stones.begin(); it != save_stones.end(); ++it )
    {
      // the call can change the set m_air_stones
      (*it)->inform_new_stone();
    }
} // player::apply_blast_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action wait.
 */
void ptb::player::apply_wait()
{ 
  if ( m_progress != &player::progress_wait ) 
    m_lazy = false;

  set_state(player::wait_state);
  m_progress = &player::progress_wait;
} // player::apply_wait()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action crouch.
 *
 */
void ptb::player::apply_crouch()
{
  m_move_force = get_move_force_in_idle();
  set_state(player::crouch_state);
  m_progress = &player::progress_crouch;
} // player::apply_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action look_upward.
 *
 */
void ptb::player::apply_look_upward()
{
  m_move_force = get_move_force_in_idle();
  set_state(player::look_upward_state);
  m_progress = &player::progress_look_upward;
} // player::apply_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Die.
 */
void ptb::player::apply_die()
{
  finish_injure();

  if ( ( game_variables::get_lives_count( m_index ) > 0 ) ||
       ( !level_variables::game_over_allowed(get_level()) ) )
    {
      if ( game_variables::get_lives_count( m_index ) > 0 )
        game_variables::set_lives_count
          ( m_index, game_variables::get_lives_count(m_index) - 1);

      bear::engine::transition_effect_message<bear::engine::fade_effect> msg;
      msg.get_effect().set_duration(0, 0.25, 0.75);
      msg.get_effect().set_color( 1, 1, 1 );
      get_level_globals().send_message
        ( PTB_TRANSITION_EFFECT_DEFAULT_TARGET_NAME, msg );
      set_state(dead_state);
      m_progress = &player::progress_dead;
    }
  else
    {
      if ( get_current_action_name() != "game_over" )
        {
          bear::engine::transition_effect_message<game_over_effect> msg;
          if ( has_world() )
            msg.get_effect().set_world( &get_world() );

          get_level_globals().send_message
            ( PTB_TRANSITION_EFFECT_DEFAULT_TARGET_NAME, msg );
          start_action_model("game_over");
          apply_game_over();
        }
    }
} // player::apply_die()

/*----------------------------------------------------------------------------*/
/**
 * \brief Roar.
 */
void ptb::player::apply_roar()
{
  set_state(roar_state);
  m_progress = &player::progress_roar;
} // player::apply_roar()

/*----------------------------------------------------------------------------*/
/**
 * \brief Disappear.
 */
void ptb::player::apply_disappear()
{
  stop_speaking();
  m_progress = &player::progress_idle;
  kill();
} // player::apply_disappear()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the state "game over".
 */
void ptb::player::apply_game_over()
{
  add_position_constraints();
  m_move_force = 0;
  set_state(game_over_state);
  m_progress = &player::progress_game_over;
} // player::apply_game_over()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to cling.
 */
void ptb::player::apply_start_cling()
{
  set_state(start_cling_state);
  m_progress = &player::progress_start_cling;
} // player::apply_start_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player cling.
 */
void ptb::player::apply_cling()
{
  m_run_time = 0;
  set_state(cling_state);
  m_progress = &player::progress_cling;
} // player::apply_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is clung and jump.
 */
void ptb::player::apply_clung_jump()
{
  if ( get_rendering_attributes().is_mirrored() )
    add_internal_force
      ( get_mass() * bear::universe::force_type(50000, 100000) );
  else
    add_internal_force
      ( get_mass() * bear::universe::force_type(-50000, 100000) );
} // player::apply_clung_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to hang.
 */
void ptb::player::apply_start_hang()
{
  set_state(start_hang_state);
  m_progress = &player::progress_start_hang;
} // player::apply_start_hang()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player hang.
 */
void ptb::player::apply_hang()
{
  set_state(hang_state);
  m_progress = &player::progress_hang;
} // player::apply_hang()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player swim.
 */
void ptb::player::apply_swimming()
{
  m_move_force = get_move_force_in_swimming();
  set_state(swimming_state);
  m_progress = &player::progress_swimming;
} // player::apply_swimming()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player swim when he is in floating.
 */
void ptb::player::apply_swim_in_float()
{
  if ( get_rendering_attributes().is_mirrored() )
    add_internal_force( bear::universe::force_type(-20000 * get_mass(), 0));
  else
    add_internal_force( bear::universe::force_type(20000 * get_mass(), 0) );
} // player::apply_swim_in_float()


/*----------------------------------------------------------------------------*/
/**
 * \brief Player swim up when he is in floating.
 */
void ptb::player::apply_swim_up_in_float()
{
  add_internal_force( bear::universe::force_type(0, 2500 * get_mass()));
} // player::apply_swim_up_in_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player sink.
 */
void ptb::player::apply_sink()
{
  m_move_force = get_move_force_in_swimming();
  set_state(sink_state);
  m_progress = &player::progress_sink;
} // player::apply_swimming()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action swim_up.
 *
 */
void ptb::player::apply_swim_up()
{
  add_internal_force( bear::universe::force_type(0, 2000 * get_mass()) );
} // player::apply_swim_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action swim_down.
 *
 */
void ptb::player::apply_swim_down()
{
  add_internal_force( bear::universe::force_type(0, -900 * get_mass()) );
} // player::apply_swim_down()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action swim_jump.
 *
 */
void ptb::player::apply_swim_jump()
{
  if ( get_rendering_attributes().is_mirrored() )
    {
      if ( m_look_upward_time )
        add_internal_force
          ( get_mass() * bear::universe::force_type(-15000, 20000));
      else if ( m_status_crouch )
        add_internal_force
          ( get_mass() * bear::universe::force_type(-15000, -1000));
      else
        add_internal_force
          ( get_mass() * bear::universe::force_type(-20000, 15000));
    }
  else
    {
      if ( m_look_upward_time )
        add_internal_force
          ( get_mass() * bear::universe::force_type(15000, 20000));
      else if ( m_status_crouch )
        add_internal_force
          ( get_mass() * bear::universe::force_type(15000, -10000));
      else
        add_internal_force
          ( get_mass() * bear::universe::force_type(20000, 15000));
    }
} // player::apply_swim_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action float.
 *
 */
void ptb::player::apply_float()
{
  m_move_force = get_move_force_in_swimming();
  set_state(float_state);
  m_progress = &player::progress_float;
} // player::apply_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action dive.
 *
 */
void ptb::player::apply_dive()
{
  add_internal_force( bear::universe::force_type(0, -2000*get_mass()));
} // player::apply_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action injured.
 */
void ptb::player::apply_injured()
{
  m_move_force = 0;
  m_nb_bottom_contact = 0;
  set_state(player::injured_state);
  m_progress = &player::progress_injured;
} // player::apply_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action paralyze.
 * \param duration The duration of the paralysation.
 */
void ptb::player::apply_paralyze(bear::universe::time_type duration)
{
  m_paralyze_duration = duration;
  set_state(player::paralyze_state);
  m_progress = &player::progress_paralyze;
  start_action_model("paralyze");
} // player::apply_paralyze()

/*----------------------------------------------------------------------------*/
/**
 * \brief Sniff.
 */
void ptb::player::apply_sniff()
{
  bear::universe::world::item_list items;

  if ( get_layer().has_world() )
    get_layer().get_world().pick_items_in_circle
      ( items, get_center_of_mass(), 
	std::numeric_limits<bear::universe::coordinate_type>::max());
  
  bear::universe::world::item_list::const_iterator it, best_item = items.end();
  bear::universe::coordinate_type best_dist = 0;
  unsigned int nb = 0;
  bool found = false;
  
  for ( it=items.begin(); it!=items.end(); ++it)
    {
      sniffable* sniff = dynamic_cast<sniffable*>(*it);
      if ( sniff != NULL ) 
	if ( game_variables::get_persistent_sniffable
	     (m_index, sniff->get_category() ) ) 
	  {
	    nb++;
	    bear::universe::coordinate_type dist = 
	      get_center_of_mass().distance((*it)->get_center_of_mass());
	    
	    if ( ( dist < best_dist ) || ! found )
	      {
		best_dist = dist;
		best_item = it;
	      }
	    found = true;
	  }
    }
} // player::apply_sniff()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose a wait state.
 */
void ptb::player::choose_wait_state()
{
  if ( ( get_bottom_contact().get_max() >= 0.6 ) && 
       ( get_bottom_contact().get_min() <= 0.4 ) )
    {
      std::ostringstream s;
      s << "wait" << (rand() % m_wait_state_number + 1);
      start_action_model(s.str());
    }
} // player::choose_wait_state()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose an idle state.
 */
void ptb::player::choose_idle_state()
{
  if ( get_bottom_contact().get_max() < 0.6 )
    {
      if ( get_rendering_attributes().is_mirrored() ) 
	start_action_model("unstable_backwards");
      else
	start_action_model("unstable_ahead");
    }
  else if ( get_bottom_contact().get_min() > 0.4 )
    {
      if ( get_rendering_attributes().is_mirrored() ) 
	start_action_model("unstable_ahead");
      else
	start_action_model("unstable_backwards");
    }
  else
    start_action_model("idle");
} // player::choose_idle_state()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose a walk state.
 */
void ptb::player::choose_walk_state()
{
  start_action_model("walk");
} // player::choose_walk_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief  Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::player::inform_no_energy(const monster& attacker)
{
  apply_die();
} // player::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief The monster is injured.
 * \param attacker The monster attacking me.
 * \param side The side on which I am attacked.
 * \param duration The duration of the injure state.
 */
void ptb::player::injure
( const monster& attacker, bear::universe::zone::position side,
  double duration)
{
  if ( get_current_action_name() != "game_over" )
    {
      const bear::engine::base_item* item =
        dynamic_cast<const bear::engine::base_item*>(&attacker);

      double orientation = -1;

      if ( item != NULL )
        if ( get_center_of_mass().x > item->get_center_of_mass().x)
          orientation = 1;

      set_speed(bear::universe::speed_type(0, 0));
      add_external_force
        ( bear::universe::force_type(orientation * 40000 * get_mass(),
          55000 * get_mass()) );
      set_bottom_contact(false);
      super::injure(attacker, side, duration);

      m_states[m_current_state]->do_injured();
      m_injured_orientation = false;
    }
} // player::injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief The monster isn't injure any more.
 */
void ptb::player::finish_injure()
{
  super::finish_injure();

  m_states[m_current_state]->do_finish_injured();
} // ptb::monster_item::finish_injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the offensive coefficient for a given attacked item and a given
 *        side.
 * \param index The index of the coefficient.
 * \param other The attacked monster.
 * \param side The side of this through which the attack is done.
 */
unsigned int ptb::player::get_offensive_coefficient
( unsigned int index, const monster& other,
  bear::universe::zone::position side ) const
{
  unsigned int result = super::get_offensive_coefficient(index, other, side);

  const base_item* item = dynamic_cast<const base_item*>(&other);
  bear::engine::model_mark_placement m;

  if ( ( item != NULL ) && ( result != 0 ) &&
       get_mark_placement("attack_point", m) )
    {
      bear::universe::rectangle_type r
        ( bear::universe::position_type( m.get_position() - m.get_size()/2),
          bear::universe::position_type( m.get_position() + m.get_size()/2) );
      if ( !item->get_bounding_box().intersects(r) )
        result = 0;
    }

  return result;
} // player::get_offensive_coefficient()

/*---------------------------------------------------------------------------*/
/**
 * \brief Progress in the water.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_in_water(bear::universe::time_type elapsed_time)
{
  create_bubble();
} // player::progress_in_water()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void ptb::player::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "oxygen_gauge: ";
  if ( m_oxygen_gauge.is_activated() )
    oss << "active : ";
  else
    oss << "not active : ";
  oss << m_oxygen_gauge.get_value() << "/"
      << m_oxygen_gauge.get_max_value() << "\n";

  oss << "heat_gauge: ";
  if ( m_heat_gauge.is_activated() )
    oss << "active : ";
  else
    oss << "not active : ";
  oss << m_heat_gauge.get_value() << "/"
      << m_heat_gauge.get_max_value() << "\n";

  oss << "cold_gauge: ";
  if ( m_cold_gauge.is_activated() )
    oss << "active : ";
  else
    oss << "not active : ";
  oss << m_cold_gauge.get_value() << "/"
      << m_cold_gauge.get_max_value() << "\n";

  oss << "state: ";
  oss << m_states[m_current_state]->get_name();
  oss << "\n";
  oss << "action: ";
  oss << get_current_action_name();
  oss << "\n";
  oss << "can_cling: " << m_can_cling << "\n";
  oss << "status_look_upward: " << m_status_look_upward << "\n";
  oss << "status_crouch: " << m_status_crouch << "\n";
  oss << "powers: " << " : ";
  if ( game_variables::get_air_power(m_index) )
    oss << "air  ";
  if ( game_variables::get_fire_power(m_index) )
    oss << "fire  ";
  if ( game_variables::get_water_power(m_index) )
    oss << "water  ";
  oss << "\n";
  oss << "air_float: ";
  if ( m_air_float )
    oss << "y";
  else
    oss << "n";
  oss << " : " << m_air_float_time;
  oss << "\n";

  str += oss.str();
} // player::to_string()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_walk( bear::universe::time_type elapsed_time )
{
  brake();

  if ( has_bottom_contact() )
    {
      if ( m_last_bottom_left == get_bottom_left() )
        choose_idle_state();
      else
        {
          bear::universe::speed_type speed( get_speed() );
          // calculate the speed in the intern axis
          bear::universe::coordinate_type speed_x =
            speed.dot_product(get_x_axis());

          if( std::abs(speed_x) >= get_speed_to_run() )
            {
              if ( m_run_time >= s_time_to_run )
                start_action_model("run");
            }
          else if ( speed_x == 0 )
            choose_idle_state();
          else
            m_move_force = get_move_force_in_walk();
        }
    }
  else
    test_in_sky_or_swimm();
} // player::progress_walk()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_idle( bear::universe::time_type elapsed_time )
{
  brake();

  if ( has_bottom_contact() )
    {
      m_run_time = 0;

      if ( ( m_state_time >= s_time_to_wait ) &&
           ( m_wait_state_number != 0 ) &&
           ( !is_a_marionette() ) &&
           m_authorized_action[player_action::wait] )
        choose_wait_state();
      else
        progress_continue_idle(elapsed_time);
    }
  else
    test_in_sky_or_swimm();
} // player::progress_idle()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration when the player stay in the state idle.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_continue_idle
( bear::universe::time_type elapsed_time )
{
  // do nothing
} // player::progress_continue_idle()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_jump( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( is_only_in_environment(bear::universe::water_environment) )
        start_action_model("sink");
      else if ( is_in_floating() )
        start_action_model("float");
      else if( get_speed().y <= 0 )
        start_action_model("fall");
    }
} // player::progress_jump()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_fall( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( is_only_in_environment(bear::universe::water_environment) )
        start_action_model("sink");
      else if ( is_in_floating() )
        start_action_model("float");
      if( get_speed().y > 0 )
        start_action_model("jump");
    }
} // player::progress_fall()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_dead( bear::universe::time_type elapsed_time )
{
  regenerate();

  start_action_model("roar");
} // player::progress_dead()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_game_over( bear::universe::time_type elapsed_time )
{
  set_status_look_upward(false);
  set_status_crouch(false);
} // player::progress_game_over()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_roar( bear::universe::time_type elapsed_time )
{
  // do_nothing
} // player::progress_roar()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_run( bear::universe::time_type elapsed_time )
{
  if ( has_bottom_contact() )
    {
      bear::universe::speed_type speed;
      speed = get_speed();

      // calculate the speed in the intern axis
      bear::universe::coordinate_type speed_x =
        speed.dot_product(get_x_axis());

      if( std::abs(speed_x) < get_speed_to_run() )
        {
          if( speed_x == 0 )
            choose_idle_state();
          else
            choose_walk_state();
        }
    }
  else
    test_in_sky_or_swimm();
} // player::progress_run()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_slap( bear::universe::time_type elapsed_time )
{
  brake();

  bear::universe::speed_type speed(get_speed());
  bear::universe::coordinate_type speed_x = speed.dot_product(get_x_axis());

  if ( get_current_action_name() == "slap" )
    {
      if ( std::abs(speed_x) != 0 )
        switch_to_model_action("slap_and_walk");
    }
  else if ( get_current_action_name() == "slap_and_walk")
    {
      if( std::abs(speed_x) == 0 )
        switch_to_model_action("slap");
    }

  if ( has_right_contact() )
    apply_move_right();
  else if ( has_left_contact() )
    apply_move_left();
} // player::progress_slap()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_start_jump( bear::universe::time_type elapsed_time )
{
  m_halo_animation->next(elapsed_time);

  brake();

  if ( !has_bottom_contact() )
    test_in_sky_or_swimm();
} // player::progress_start_jump()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_vertical_jump
( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    if( get_speed().y <= 0 )
      start_action_model("fall");
} // player::progress_vertical_jump()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_crouch( bear::universe::time_type elapsed_time )
{
  brake();

  if ( !has_bottom_contact() )
    test_in_sky_or_swimm();
} // player::progress_crouch()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_look_upward( bear::universe::time_type elapsed_time )
{
  brake();

  if ( !has_bottom_contact() )
    test_in_sky_or_swimm();
} // player::progress_look_upward()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state captive.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_captive( bear::universe::time_type elapsed_time )
{
  // do nothing
} // player::progress_captive()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state paralyze.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_paralyze( bear::universe::time_type elapsed_time )
{
  if ( m_state_time >= m_paralyze_duration )
    choose_idle_state();
} // player::progress_paralyze()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_throw( bear::universe::time_type elapsed_time )
{
  brake();

  bear::universe::speed_type speed(get_speed());
  bear::universe::coordinate_type speed_x = speed.dot_product(get_x_axis());

  if ( get_current_action_name() == "throw" )
    {
      if ( !has_bottom_contact() )
        switch_to_model_action("throw_and_fall");
      else if( std::abs(speed_x) != 0 )
        switch_to_model_action("throw_and_walk");
    }
  else if ( get_current_action_name() == "throw_and_walk")
    {
      if ( !has_bottom_contact() )
        switch_to_model_action("throw_and_fall");
      else if( std::abs(speed_x) == 0 )
        switch_to_model_action("throw");
    }
  else if ( get_current_action_name() == "throw_and_fall")
    {
      if ( has_bottom_contact() )
        {
          if( std::abs(speed_x) == 0 )
            switch_to_model_action("throw");
          else
            switch_to_model_action("throw_and_walk");
        }
    }
} // player::progress_throw()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_maintain( bear::universe::time_type elapsed_time )
{
  brake();

  bear::universe::speed_type speed(get_speed());
  bear::universe::coordinate_type speed_x = speed.dot_product(get_x_axis());

  if ( get_current_action_name() == "maintain" )
    {
      if ( !has_bottom_contact() )
        switch_to_model_action("maintain_and_fall");
      else if( std::abs(speed_x) != 0 )
        switch_to_model_action("maintain_and_walk");
    }
  else if ( get_current_action_name() == "maintain_and_walk" )
    {
      if ( !has_bottom_contact() )
        switch_to_model_action("maintain_and_fall");
      else if( std::abs(speed_x) == 0 )
        switch_to_model_action("maintain");
    }
  else if ( get_current_action_name() == "maintain_and_fall" )
    {
      if ( has_bottom_contact() )
        {
          if( std::abs(speed_x) == 0 )
            switch_to_model_action("maintain");
          else
            switch_to_model_action("maintain_and_walk");
        }
    }
} // player::progress_maintain()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_wait( bear::universe::time_type elapsed_time )
{
  brake();
  
  if ( ( m_state_time > 10 ) && ( ! m_lazy ) )
    {
      m_lazy = true;
      status_layer_notification_message msg;
      
      bear::visual::sprite sp;
      msg.set_notification( get_index(), sp, gettext("lazy player"));
      
      get_level_globals().send_message
	( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
    }

  if ( !has_bottom_contact() )
    test_in_sky_or_swimm();
} // player::progress_wait()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_start_cling
( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( ( !get_rendering_attributes().is_mirrored()
             && has_right_contact() ) ||
           ( get_rendering_attributes().is_mirrored() && has_left_contact() ) )
        {
          if ( m_can_cling )
            {
              m_cling_orientation = get_rendering_attributes().is_mirrored();
              start_action_model("cling");
            }
          else
            choose_idle_state();
        }
    }
} // player::progress_start_cling()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_cling( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( has_top_contact() || ( !m_can_cling  ) )
        start_action_model("fall");
      else
        {
          get_rendering_attributes().mirror(m_cling_orientation);

          bear::universe::speed_type speed = get_speed();
          speed.x = 0;
          if ( speed.y > 0 )
            speed.y = 0;
          else
            speed.y *= 0.9;

          set_speed(speed);

          if ( get_layer().has_world() )
            {
              bear::universe::force_type force
                ( - get_mass() * get_layer().get_world().get_gravity() );

              if ( (get_density() != 0) &&
                   ( get_mass() != std::numeric_limits<double>::infinity() )  )
                force += get_layer().get_world().get_gravity() * get_mass() *
                  get_layer().get_world().get_average_density
                  (get_bounding_box()) / get_density();

              add_external_force(force);
            }
        }
    }
} // player::progress_cling()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_clung_jump
( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    if( get_speed().y <= 0 )
      start_action_model("fall");
} // player::progress_clung_jump()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_start_hang
( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( ( !get_rendering_attributes().is_mirrored() &&
             has_right_contact() ) ||
           ( get_rendering_attributes().is_mirrored() && has_left_contact() ) )
        start_action_model("hang");
      else
        if ( m_state_time >= s_max_time_to_hang )
          choose_idle_state();
    }
} // player::progress_start_hang()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_hang( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( has_top_contact() )
        start_action_model("fall");
      else if ( get_layer().has_world() )
        add_external_force
          (- get_mass() * get_layer().get_world().get_gravity());
    }
} // player::progress_hang()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_swimming( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( !is_only_in_environment(bear::universe::water_environment) )
        {
          if ( is_in_floating() )
            start_action_model("float");
          else if( get_speed().y <= 0 )
            start_action_model("fall");
          else
            start_action_model("jump");
        }
    }

  m_look_upward_time = 0;
  m_crouch_time = 0;
} // player::progress_swimming()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_sink( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( !is_only_in_environment(bear::universe::water_environment) )
        {
          if ( is_in_floating() )
            start_action_model("float");
          else if( get_speed().y > 0 )
            start_action_model("jump");
          else
            start_action_model("fall");
        }
    }

  if ( get_current_action_name() == "sink" )
    {
      if ( m_status_crouch )
        get_action(get_current_action_name())->get_mark
          (get_mark_id("body")).get_animation()->set_time_factor(1.5);
      else if ( m_status_look_upward )
        get_action(get_current_action_name())->get_mark
          (get_mark_id("body")).get_animation()->set_time_factor(0.6);
      else
        get_action(get_current_action_name())->get_mark
          (get_mark_id("body")).get_animation()->set_time_factor(1);

    }

  m_look_upward_time = 0;
  m_crouch_time = 0;
} // player::progress_sink()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_float( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( is_only_in_environment(bear::universe::water_environment) )
        {
          start_action_model("sink");
        }
      else if ( !is_in_floating() )
        {
          if( get_speed().y > 0 )
            start_action_model("jump");
          else
            start_action_model("fall");
        }
    }
} // player::progress_float()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_injured( bear::universe::time_type elapsed_time )
{
  brake();

  if ( has_bottom_contact() )
    {
      ++m_nb_bottom_contact;

      if ( m_nb_bottom_contact > 2 )
        {
          if ( m_last_bottom_left == get_bottom_left() )
            choose_idle_state();
          else
            {
              bear::universe::speed_type speed( get_speed() );
              // calculate the speed in the intern axis
              bear::universe::coordinate_type speed_x =
                speed.dot_product(get_x_axis());

              if( std::abs(speed_x) >= get_speed_to_run() )
                start_action_model("run");
              else if ( speed_x == 0 )
                choose_idle_state();
              else
                choose_walk_state();
            }
        }
    }
} // player::progress_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the state of Player.
 */
void ptb::player::set_state(player_state_name state)
{
  if ( state != m_current_state )
    {
      m_states[m_current_state]->stop();
      m_current_state = state;
      m_states[m_current_state]->start();
      m_state_time = 0;
    }
} // player::set_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Test if Player is crushed.
 */
bool ptb::player::is_crushed() const
{
  return ( ( has_bottom_contact() && has_top_contact() ) ||
           ( has_right_contact() && has_left_contact() ) );
} // player::is_crushed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Spawn the player after his death.
 * \todo Game over if the player has no more lifes.
 * \todo Update lifes and any other counters.
 */
void ptb::player::regenerate()
{
  set_center_of_mass( m_saved_position );
  stop();
  m_energy = game_variables::get_max_energy(m_index);
  m_signals.energy_added(m_energy);

  if ( m_invincible )
    {
      bear::engine::transition_effect_erase_message msg
        (m_invincible_id_effect);
      get_level_globals().send_message
        ( PTB_TRANSITION_EFFECT_DEFAULT_TARGET_NAME, msg );
      m_invincible_time = 0;
      set_invincible(false);
    }
  m_last_visual_time = 0;
  m_last_visuals.clear();
  m_run_time = 0;
  m_can_cling = false;
  set_air_float(false);
  m_lazy = false;
  m_injured_orientation = true;
  m_want_clung_jump = false;
  game_variables::set_air_power(m_index, false);
  game_variables::set_fire_power(m_index, false);
  game_variables::set_water_power(m_index, false);
  update_powers();
  m_oxygen_gauge.set_value(s_max_oxygen_gauge);
  m_heat_gauge.set_value(s_max_heat_gauge);
  m_cold_gauge.set_value(s_max_cold_gauge);
  m_air_stones.clear();
  m_move_right = false;
  m_move_left = false;
  m_last_bottom_left = bear::universe::position_type(0, 0);
  get_rendering_attributes().mirror(false);
  stop_speaking();

  m_animation_to_throw = bear::visual::animation();
  remove_all_links();
  finish_injure();
  super::injure(*this, bear::universe::zone::middle_zone, 5);
} // player::regenerate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Player has a power.
 */
bool ptb::player::has_a_power() const
{
  return game_variables::get_air_power(m_index) ||
    game_variables::get_fire_power(m_index) ||
    game_variables::get_water_power(m_index);
} // player::has_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Player has all powers.
 */
bool ptb::player::has_all_powers() const
{
  return game_variables::get_air_power(m_index) &&
    game_variables::get_fire_power(m_index) &&
    game_variables::get_water_power(m_index);
} // player::has_powers()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Player is in the water and in the air.
 */
bool ptb::player::is_in_floating() const
{
  bool result = false;

  if ( get_layer().has_world() )
    {
      std::set<bear::universe::environment_type> environments;
      get_layer().get_world().get_environments
        (get_bounding_box(), environments);
      result =
        ( environments.find(bear::universe::water_environment)
          != environments.end() )
        && ( environments.size() >= 1 );
    }

  return result;
} // player::is_in_floatting()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the orientation.
 */
void ptb::player::update_orientation()
{
  if ( get_current_action_name()!= "captive" )
    {
      if ( get_speed().x < 0 )
	{
	  if ( ( !is_injured() ) ||
	       ( m_injured_orientation &&
		 ( get_current_action_name()!= "injured" ) ) )
	    get_rendering_attributes().mirror(true);
	  else
	    get_rendering_attributes().mirror(false);
	}
      else if ( get_speed().x > 0 )
	{
	  if ( ( !is_injured() ) ||
	       ( m_injured_orientation &&
		 ( get_current_action_name()!= "injured" ) ) )
	    get_rendering_attributes().mirror(false);
	  else
	    get_rendering_attributes().mirror(true);
	}
    }
} // player::update_orientation()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the offensive and defensive parameters according to a power.
 * \param b The power status.
 * \param a The corresponding attack
 */
void ptb::player::update_power( bool b, monster::attack_type a)
{
  if ( b )
    {
      m_defensive_powers[a] = true;
      m_offensive_coefficients[a] = 1;
    }
  else
    {
      m_defensive_powers[a] = false;
      m_offensive_coefficients[a] = 0;
    }
} // player::update_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the offensive and defensive parameters according to
 * the powers.
 */
void ptb::player::update_powers()
{
  update_power(game_variables::get_air_power(m_index), monster::air_attack);
  update_power(game_variables::get_fire_power(m_index), monster::fire_attack);
  update_power(game_variables::get_water_power(m_index), monster::water_attack);

  if ( has_a_power() && ( m_halo_hand_animation != NULL ) )
    {
      if ( game_variables::get_air_power(m_index) )
        if ( game_variables::get_fire_power(m_index) )
          if ( game_variables::get_water_power(m_index) )
            m_halo_hand_animation->set_intensity(0.5, 0.5, 0.5);
          else
            m_halo_hand_animation->set_intensity(1, 0, 0);
        else
          if ( game_variables::get_water_power(m_index) )
            m_halo_hand_animation->set_intensity(0.19, 0.78, 0.94);
          else
            m_halo_hand_animation->set_intensity(1, 1, 1);
      else
        if ( game_variables::get_fire_power(m_index) )
          if ( game_variables::get_water_power(m_index) )
            m_halo_hand_animation->set_intensity(1, 0.5, 0);
          else
            m_halo_hand_animation->set_intensity(0.66, 0.13, 0);
        else
          if ( game_variables::get_water_power(m_index) )
            m_halo_hand_animation->set_intensity(0, 0, 1);
    }
} // player::update_powers()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the camera on the current player.
 */
void ptb::player::do_get_camera()
{
  shared_camera::placement_mode mode;

  if ( get_name() == util::get_player_name(1) )
    mode = shared_camera::lock_first_player;
  else
    mode = shared_camera::lock_second_player;

  shared_camera::set_placement_message msg(mode);
  bear::engine::level_globals& glob = get_level_globals();

  glob.send_message( "camera", msg );
} // player::do_get_camera()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to look up.
 */
void ptb::player::do_stop_look_upward()
{
  m_status_look_upward = false;
  m_states[m_current_state]->do_stop_look_upward();
} // state_player::do_stop_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to crouch.
 */
void ptb::player::do_stop_crouch()
{
  m_status_crouch = false;
  m_states[m_current_state]->do_stop_crouch();
} // state_player::do_stop_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the corrupting bonus attractor.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_corrupting_bonus_attractor
( bear::universe::time_type elapsed_time )
{
  if ( has_all_powers() )
    {
      if ( m_corrupting_bonus_attractor == NULL )
        create_corrupting_bonus_attractor();
    }
  else if ( m_corrupting_bonus_attractor != NULL )
    {
      m_corrupting_bonus_attractor->kill();
      m_corrupting_bonus_attractor = NULL;
    }
} // player::progress_corrupting_bonus_attractor

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the gauges.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_gauges( bear::universe::time_type elapsed_time )
{
  progress_oxygen_gauge(elapsed_time);
  progress_heat_gauge(elapsed_time);
  progress_cold_gauge(elapsed_time);
} // player::progress_gauges()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the oxygen_gauge.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_oxygen_gauge
( bear::universe::time_type elapsed_time )
{
  bool in_water(is_in_environment(bear::universe::water_environment));
  double last_value( m_oxygen_gauge.get_value());

  bear::engine::model_mark_placement m;

  if ( ( is_in_environment(bear::universe::water_environment) ) &&
       ( !game_variables::get_water_power(m_index) ) )
    {
      if ( get_mark_placement("mouth", m) && get_layer().has_world() )
        {
          if ( get_layer().get_world().is_in_environment
               (m.get_position(), bear::universe::water_environment) )
            m_oxygen_gauge.remove_value
              (s_oxygen_loss_speed*elapsed_time);
          else
            m_oxygen_gauge.add_value
              (s_oxygen_inspiration_speed*elapsed_time);
        }
      else
        m_oxygen_gauge.remove_value(s_oxygen_loss_speed*elapsed_time);
    }
  else
    m_oxygen_gauge.add_value(s_oxygen_loss_speed*elapsed_time);

  if ( m_oxygen_gauge.get_value() == 0 )
    remove_energy(*this, 0.1);

  if ( m_oxygen_gauge.get_value() != last_value )
    m_signals.oxygen_gauge_changed(m_oxygen_gauge.get_value());

  if ( ( !m_oxygen_gauge.is_activated() ) && in_water )
    m_signals.enters_water_zone();
  else if ( m_oxygen_gauge.is_activated() && ( !in_water ) )
    m_signals.leaves_water_zone();

  m_oxygen_gauge.set_activated(in_water);
} // player::progress_oxygen_gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the heat_gauge.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_heat_gauge( bear::universe::time_type elapsed_time )
{
  bool in_fire(is_in_environment(bear::universe::fire_environment));
  double last_value( m_heat_gauge.get_value());

  if ( is_only_in_environment(bear::universe::fire_environment) )
    m_heat_gauge.remove_value(s_fire_loss_speed*elapsed_time);
  else
    m_heat_gauge.add_value(s_fire_increase_speed*elapsed_time);

  if ( m_heat_gauge.get_value() == 0 )
    remove_energy(*this, 0.1);

  if ( m_heat_gauge.get_value() != last_value )
    m_signals.heat_gauge_changed(m_heat_gauge.get_value());

  if ( ( !m_heat_gauge.is_activated() ) && in_fire )
    m_signals.enters_heat_zone();
  else if ( m_heat_gauge.is_activated() && ( !in_fire ) )
    m_signals.leaves_heat_zone();

  m_heat_gauge.set_activated(in_fire);
} // player::progress_heat_gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the cold_gauge.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_cold_gauge( bear::universe::time_type elapsed_time )
{
  bool in_ice(is_in_environment(bear::universe::ice_environment));
  double last_value( m_cold_gauge.get_value());

  if ( is_only_in_environment(bear::universe::ice_environment) )
    m_cold_gauge.remove_value(s_ice_loss_speed*elapsed_time);
  else
    m_cold_gauge.add_value(s_ice_increase_speed*elapsed_time);

  if ( m_cold_gauge.get_value() == 0 )
    remove_energy(*this, 0.1);

  if ( m_cold_gauge.get_value() != last_value )
    m_signals.cold_gauge_changed(m_cold_gauge.get_value());

  if ( ( !m_cold_gauge.is_activated() ) && in_ice )
    m_signals.enters_cold_zone();
  else if ( m_cold_gauge.is_activated() && ( !in_ice ) )
    m_signals.leaves_cold_zone();

  m_cold_gauge.set_activated(in_ice);
} // player::progress_cold_gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the spot.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_spot( bear::universe::time_type elapsed_time )
{
  bool balance_x(true);
  bool balance_y(true);

  if ( m_status_look_upward )
    {
      m_look_upward_time += elapsed_time;

      if ( m_look_upward_time >= s_time_to_look_upward )
        {
          balance_y = false;
          add_spot_gap( bear::universe::position_type(0, 5) );
        }
    }

  if ( m_status_crouch )
    {
      m_crouch_time += elapsed_time;

      if ( m_crouch_time >= s_time_to_crouch )
        {
          balance_y = false;
          add_spot_gap( bear::universe::position_type(0, -5) );
        }
    }

  if ( get_speed().x > get_speed_to_run() )
    {
      set_spot_maximum(200, 220);
      balance_x = false;
      add_spot_gap( bear::universe::position_type(3, 0) );
    }
  else if ( get_speed().x < -get_speed_to_run() )
    {
      set_spot_minimum(-200, -250);
      balance_x = false;
      add_spot_gap( bear::universe::position_type(-3, 0) );
    }
  else if ( get_speed().x > ( get_speed_to_run() / 2 ) )
    {
      set_spot_maximum(100, 220);
      balance_x = false;
      add_spot_gap( bear::universe::position_type(1, 0) );
    }
  else if ( get_speed().x < (- get_speed_to_run() / 2) )
    {
      set_spot_minimum(-100, -250);
      balance_x = false;
      add_spot_gap( bear::universe::position_type(-1, 0) );
    }

  balance_spot(balance_x, balance_y);
} // player::progress_spot()

/*---------------------------------------------------------------------------*/
/**
 * \brief Stop the player (speed and force).
 */
void ptb::player::stop()
{
  set_state(idle_state);
  choose_idle_state();
  set_speed( bear::universe::speed_type(0, 0) );
  set_internal_force(bear::universe::force_type(0, 0));
  set_external_force(bear::universe::force_type(0, 0));
} // player::stop()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if Player walk and change state thereof.
 *         Return true if Player walk.
 */
bool ptb::player::test_walk()
{
  bool result = false;

  if ( has_bottom_contact() )
    {
      bear::universe::speed_type speed;
      speed = get_speed();
      // calculate the speed in the intern axis
      bear::universe::coordinate_type speed_x =
        speed.dot_product(get_x_axis());

      if( std::abs(speed_x) >= get_speed_to_run() )
        {
          result = true;
          start_action_model("run");
        }
      else if ( ( speed_x != 0 ) &&
                ( get_bottom_left() != m_last_bottom_left ) )
        {
          result = true;
          choose_walk_state();
        }
    }

  return result;
} // player::test_walk()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if Player walk, run or is idle and change state thereof.
 *         Return true if Player has a bottom contact.
 */
bool ptb::player::test_bottom_contact()
{
  bool result = false;

  if ( has_bottom_contact() )
    {
      bear::universe::speed_type speed;
      speed = get_speed();

      // calculate the speed in the intern axis
      bear::universe::coordinate_type speed_x =
        speed.dot_product(get_x_axis());

      if( std::abs(speed_x) >= get_speed_to_run() )
        start_action_model("run");
      else if( speed_x != 0 )
        choose_walk_state();
      else
        choose_idle_state();

      result = true;
    }

  return result;
} // player::test_bottom_contact()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if Player is in the sky or swimm and change state thereof.
 *         Return true if Player is in the sky.
 */
bool ptb::player::test_in_sky_or_swimm()
{
  bool result = false;

  if ( !has_bottom_contact() )
    {
      result = true;

      if ( is_only_in_environment(bear::universe::water_environment) )
        start_action_model("sink");
      else if ( is_in_floating() )
        start_action_model("float");
      else if( get_speed().y <= 0 )
        start_action_model("fall");
      else
        start_action_model("jump");
    }

  return result;
} // player::test_in_sky_or_swimm()

/*---------------------------------------------------------------------------*/
/**
 * \brief Brake on x axis if Player has no direction.
 */
void ptb::player::brake()
{
  if ( !m_move_right && !m_move_left )
    {
      bear::universe::speed_type speed = get_speed();
      speed.x *= 0.9;
      set_speed(speed);
    }
  m_move_right = false;
  m_move_left = false;
} // player::brake()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a bubble.
 */
void ptb::player::create_bubble()
{
  if ( (rand() % 100) == 0 )
    {
      bear::engine::model_mark_placement m;
      if ( get_mark_placement("mouth", m) )
        {
          bear::universe::position_type pos( m.get_position() );

          air_bubble* new_bubble;

          new_bubble= new air_bubble();
          new_bubble->set_z_position(get_z_position() + 1);
          new_bubble->set_oxygen(0);
          new_bubble->set_center_of_mass(pos);
          new_item( *new_bubble );
        }
    }
} // player::create_bubble()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration when plee receives energy.
 */
void ptb::player::create_soul_decoration()
{
  bear::star* new_decoration =
    new bear::star
    ( 8, 0.75, bear::visual::color_type(196, 211, 221, 255), 1,
      bear::visual::color_type(233, 233, 236, 255) );

  //new_decoration->set_kill_when_leaving(true);
  new_decoration->set_z_position(get_z_position() - 1);
  if ( get_rendering_attributes().is_mirrored() )
    new_decoration->get_rendering_attributes().mirror(true);

  new_decoration->get_rendering_attributes().set_angle(0.786);
  new_decoration->set_size( 200, 200 );
  new_item( *new_decoration );
  new_decoration->set_center_of_mass(get_center_of_mass());

  const bear::universe::time_type d(0.6);
  bear::universe::forced_tracking mvt(d);
  mvt.set_reference_point_on_center( *this );
  new_decoration->set_forced_movement(mvt);

  bear::decorative_effect* decoration_effect = new bear::decorative_effect;

  decoration_effect->set_duration(d);
  decoration_effect->set_size_factor(0.5, 3);
  bear::visual::color init_color, end_color;
  init_color.set(1,1,1,0.8);
  end_color.set(1,1,1,0);
  decoration_effect->set_color( init_color, end_color );
  decoration_effect->set_angle_offset(0, 3.14159);
  decoration_effect->set_item(new_decoration, true);

  new_item( *decoration_effect );

  shake(15, 0.5);
} // player::create_soul_decoration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create an attractor of corrupting_bonus.
 */
void ptb::player::create_corrupting_bonus_attractor()
{
  CLAW_ASSERT( m_corrupting_bonus_attractor == NULL,
              "There already exist a corrupting bonus attractor." );
  m_corrupting_bonus_attractor = new corrupting_bonus_attractor;

  new_item( *m_corrupting_bonus_attractor );
  m_corrupting_bonus_attractor->set_center_of_mass(get_center_of_mass());

  // add forced movement to stay on the player
  bear::universe::forced_tracking movement
    ( bear::universe::position_type(0, 0) );

  movement.set_reference_point_on_center( *this );

  m_corrupting_bonus_attractor->set_forced_movement( movement );
} // player::create_corrupting_bonus_attractor()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the item displaying the powers.
 */
void ptb::player::create_power_effect()
{
  power_effect* e = new power_effect();

  new_item( *e );
  e->set_player_index(get_index());

  e->set_center_of_mass(get_center_of_mass());

  // add forced movement to stay on the player
  bear::universe::forced_tracking movement
    ( bear::universe::position_type(0, 0) );

  movement.set_reference_point_on_center( *this );

  e->set_forced_movement( movement );
} // player::create_power_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call shake with the arguments corresponding to a roar.
 */
void ptb::player::roar_shake()
{
  shake(20, 1);
} // roar_shake()

/*----------------------------------------------------------------------------*/
/**
 * \brief Shake the camera.
 * \param force The force of the shaker.
 * \param duration The duration of the shaker.
 */
void ptb::player::shake(double force, bear::universe::time_type duration) const
{
  bear::camera_shaker::shake_around( *this, force, duration );
} // player::shake()

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the sprite of the soul.
 */
bear::visual::sprite ptb::player::get_soul_sprite() const
{
  return bear::visual::sprite();
} // player::get_soul_sprite()

/*----------------------------------------------------------------------------*/
/**
 * \brief Compute the ejection force of object.
 */
bear::universe::force_type ptb::player::get_object_force() const
{
  double force;
  bear::universe::force_type result;

  if ( m_throw_up && !m_throw_down)
    {
      force = 4 + 4 * m_throw_time_ratio;
      result.x = 1;
      result.y = 5;
    }
  else if ( !m_throw_up && m_throw_down)
    {
      force = 1 + 6 * m_throw_time_ratio;
      result.x = 4;
      result.y = -1;
    }
  else
    {
      force = 3 + 5 * m_throw_time_ratio;
      result.x = 3;
      result.y = 3;
    }

  result *= 3500;

  if ( get_rendering_attributes().is_mirrored() )
    result.x = -result.x;

  result.x = result.x * force + 100*get_speed().x;
  result.y = result.y * force + get_speed().y;

  return result;
} // player::get_object_force()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render halos.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void ptb::player::render_halos
( std::list<bear::engine::scene_visual>& visuals ) const
{
  render_jump_halo(visuals);
  render_hand_halo(visuals);
} // player::render_halos()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render jump halo.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void ptb::player::render_jump_halo
( std::list<bear::engine::scene_visual>& visuals ) const
{
  if ( m_current_state == player::start_jump_state )
    {
      bear::universe::size_type height
        ( s_max_halo_height * (m_state_time / s_time_to_jump) );

      bear::visual::sprite current_sprite(m_halo_animation->get_sprite());
      current_sprite.set_height((unsigned int)height);
      current_sprite.set_angle
        ( current_sprite.get_angle() + get_visual_angle() );

      visuals.push_front
        ( bear::engine::scene_visual
          ( get_bottom_middle().x - current_sprite.width() / 2,
            get_bottom(),
            current_sprite, get_z_position()+1 ) );
    }
} // player::render_jump_halo()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render halos.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void ptb::player::render_hand_halo
( std::list<bear::engine::scene_visual>& visuals ) const
{
  if ( has_a_power()
       && ( (m_current_state == player::maintain_state)
            || (m_current_state == player::throw_state) )
       && ( m_throwable_items.get_current_throwable_item()->get_name()
            == "stone" ) )
    {
      bear::visual::sprite current_sprite(m_halo_hand_animation->get_sprite());
      double angle(current_sprite.get_angle() + get_visual_angle() );
      bear::engine::model_mark_placement m;

      if ( get_mark_placement("hand_over", m) )
        if ( m.is_visible() )
          {
            bear::universe::position_type pos( m.get_position() );
            angle += m.get_angle();

            current_sprite.set_angle(angle);
            visuals.push_front
              ( bear::engine::scene_visual
                ( pos.x - current_sprite.width() / 2,
                  pos.y - current_sprite.height() / 2,
                  current_sprite, get_z_position()+1 ) );
          }
    }
} // player::render_hand_halo()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the throw state.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void ptb::player::render_throw
( std::list<bear::engine::scene_visual>& visuals ) const
{
  if ( (m_current_state == player::throw_state)
       && m_animation_to_throw.is_valid() )
    {
      bear::engine::model_mark_placement m;

      if ( get_mark_placement("hand", m) )
        if ( m.is_visible() )
          {
            bear::visual::sprite current_sprite
              (m_animation_to_throw.get_sprite());

            const double angle
              ( current_sprite.get_angle() + get_visual_angle()
                + m.get_angle() );
            bear::universe::position_type pos = m.get_position();
            current_sprite.set_angle(angle);

            visuals.push_front
              ( bear::engine::scene_visual
                ( pos.x - current_sprite.width() / 2,
                  pos.y - current_sprite.height() / 2,
                  current_sprite, m.get_depth_position() ) );
          }
    }
} // player::render_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item without invincible visuals.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void
ptb::player::get_visuals_without_invincibility
( std::list<bear::engine::scene_visual>& visuals ) const
{
  super::get_visual(visuals);

  render_halos(visuals);
  render_throw(visuals);
} // player::get_visuals_without_invincibility()

/*---------------------------------------------------------------------------*/
/**
 * \brief Progress the invincibility statut.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_invincibility
( bear::universe::time_type elapsed_time )
{
  m_last_visual_time += elapsed_time;

  if ( is_invincible() )
    {
      m_invincible_time += elapsed_time;
      if ( m_invincible_time >= invincibility_effect::get_total_duration() )
        set_invincible(false);
    }

  if ( m_last_visual_time > 0.03 )
    {
      m_last_visual_time = 0;      
      
      if ( is_invincible() )
        {
	  create_invincible_star();
          if ( m_last_visuals.size() > 6 )
            m_last_visuals.pop_front();

          std::list<bear::engine::scene_visual> visuals;
          get_visuals_without_invincibility(visuals);

          std::list<bear::engine::scene_visual>::iterator it;
          for ( it = visuals.begin(); it != visuals.end(); ++it )
            it->scene_element.get_rendering_attributes().set_intensity
              (1, 0.5, 0.5);

          m_last_visuals.push_back(visuals);
        }
      else if ( !m_last_visuals.empty() )
        m_last_visuals.pop_front();

      std::list< std::list<bear::engine::scene_visual> >::iterator it;

      for ( it = m_last_visuals.begin(); it != m_last_visuals.end(); ++it )
        {
          std::list<bear::engine::scene_visual>::iterator it2;

          for (it2 = it->begin(); it2 != it->end(); ++it2 )
            it2->scene_element.get_rendering_attributes().set_opacity
              ( 0.8 *
                it2->scene_element.get_rendering_attributes().get_opacity());
        }
    }
} // player::progress_invincibilty()

/*---------------------------------------------------------------------------*/
/**
 * \brief Progress the air_float movement.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player::progress_air_float
( bear::universe::time_type elapsed_time )
{
  m_air_float_time += elapsed_time;

  if ( m_air_float_time >= s_max_time_air_float )
    m_air_float = false;
  else
    {
      if ( get_speed().y < 0 )
        {
          double r=(double)rand()/(double)RAND_MAX;

          if ( get_layer().has_world() )
            {
              bear::universe::force_type force
                ( -(0.5+r/2)*get_mass() *
                  get_layer().get_world().get_gravity() );

              if ( (get_density() != 0) &&
                   ( get_mass() != std::numeric_limits<double>::infinity() )  )
                force += get_layer().get_world().get_gravity() * get_mass() *
                  get_layer().get_world().get_average_density
                  (get_bounding_box()) / get_density();

              add_external_force(force);
            }
        }
    }
} // progress_air_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a star to show a hit.
 * \param that The item being attacked by this.
 */
void ptb::player::create_hit_star( const bear::engine::base_item& that ) const
{
  bear::engine::model_mark_placement m;
  get_mark_placement("hand", m);
  super::create_hit_star( m.get_position(), m.get_angle() );
} // player::create_hit_star()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a star when player is invincible.
 */
void ptb::player::create_invincible_star()
{
  bear::star* s =
    new bear::star
    ( 5, 0.5, bear::visual::color(145, 145, 145), 1,
      bear::visual::color(200, 200, 20) );

  unsigned int width = rand()%20 + 10;
  s->set_size(width, width);
  s->set_z_position(  get_z_position() + 1 );
  s->set_system_angle( rand() % 100 );
  s->set_system_angle_as_visual_angle(true);
  s->set_center_of_mass
    ( get_left() + rand() % (int)get_width(),
      get_bottom() + rand() % (int)get_height());

  new_item(*s);
  bear::universe::forced_tracking m;
  m.set_reference_point_on_center(*this);
  s->set_forced_movement(m);
  
  const claw::tween::single_tweener tweener
    ( 1, 0, 0.4,
      boost::bind
      ( &bear::visual::bitmap_rendering_attributes::set_opacity,
        &(s->get_rendering_attributes()), _1 ), 
      &claw::tween::easing_linear::ease_in );

  bear::tweener_item* t = new bear::tweener_item(tweener, s, true);
  
  new_item( *t );
} // player::create_invincible_star()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the default throwable items.
 */
void ptb::player::fill_throwable_items()
{
  m_throwable_items.add( new stone_throwable_item(this) );
  m_throwable_items.add( new air_honeypot_throwable_item(this) );
  m_throwable_items.add( new fire_honeypot_throwable_item(this) );
  m_throwable_items.add( new water_honeypot_throwable_item(this) );
  m_throwable_items.add( new hazelnut_throwable_item(this) );
} // player::fill_throwable_items()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a throwable item for the corrupting item.
 * \param amount The amount of corrupting items per throw.
 * \param coeff The amount of corrupting items used per each unit of energy lost
 *        by the boss.
 * \param anim The animation of the corrupting item.
 */
void ptb::player::add_corrupting_item
( double amount, double coeff, const std::string& anim )
{
  corrupting_item item(amount / game_variables::get_players_count());
  item.set_animation( get_level_globals().get_animation(anim) );

  m_throwable_items.add
    ( new corrupting_item_throwable_item(anim, item, coeff) );
  m_throwable_items.select( "corrupting_item" );
} // player::add_corrupting_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the default throwable items.
 */
void ptb::player::remove_corrupting_item()
{
  delete m_throwable_items.remove( "corrupting_item" );
} // player::remove_corrupting_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::player::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_roar, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_disappear, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_game_over, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_captive, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_crouch, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_fall, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_float, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_idle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_look_upward, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_run, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_sink, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_slap, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_attack, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_start_cling, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_start_hang, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_cling, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_hang, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_clung_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_throw, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_maintain, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_start_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_swimming, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_vertical_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_wait, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_walk, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_throw_object, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_injured, void );
  TEXT_INTERFACE_CONNECT_METHOD_1
    ( player, apply_paralyze, void, bear::universe::time_type );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_swim_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_swim_in_float, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_swim_up_in_float, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_sniff, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, roar_shake, void );

  TEXT_INTERFACE_CONNECT_METHOD_0( player, save_current_position, void );

  TEXT_INTERFACE_CONNECT_METHOD_1
    ( player, authorize_action, void, const std::string& );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, authorize_all_actions, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, disable_all_actions, void );
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( player, add_corrupting_item, void, double, double, const std::string& );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, remove_corrupting_item, void );
} // player::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::player )
