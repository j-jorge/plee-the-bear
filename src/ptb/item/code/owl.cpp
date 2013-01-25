/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::owl class.
 * \author Julien Jorge
 */
#include "ptb/item/owl.hpp"
#include "ptb/item/bonus_points/bonus_points.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/item/hazelnut.hpp"
#include "ptb/message/status_layer_notification_message.hpp"

#include "engine/function/bool_level_variable_getter.hpp"
#include "engine/game.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( owl, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::owl::owl()
  : sniffable("owl"), 
    m_action(action_idling), m_progress(NULL), m_has_hazelnut(false)
{
  set_phantom(true);
} // owl::owl()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::owl::pre_cache()
{
  get_level_globals().load_model("model/owl.cm");
} // owl::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void ptb::owl::on_enters_layer()
{
  super::on_enters_layer();

  create_level_bonus();

  if ( m_other_player.empty() )
    m_other_player.push_back( gettext("Did you lose your friend?") );

  if ( m_already_have.empty() )
    m_already_have.push_back
      ( gettext("You already gave me my lucky hazelnut. Stop bothering me!") );

  if ( m_happy.empty() )
    m_happy.push_back( gettext("So you found my lucky hazelnut!") );

  if ( m_want_hazelnut.empty() )
    m_want_hazelnut.push_back
      ( gettext("I'd like to have my lucky hazelnut back.") );

  if ( m_goodbye.empty() )
    m_goodbye.push_back( gettext("See you in another world.") );

  if ( m_receive_hazelnut.empty() )
    m_receive_hazelnut.push_back
      ( gettext("I've been looking all over for it!") );

  set_model_actor( get_level_globals().get_model("model/owl.cm") );

  start_model_action("idle");
} // owl::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::owl::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if ( !m_activated )
    m_action = action_idling;

  if ( has_finished_to_speak() )
    start_model_action("idle");

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);

  m_activated = false;
} // owl::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the owl is well initialized.
 */
bool ptb::owl::is_valid() const
{
  return super::is_valid() && !m_level_name.empty();
} // owl::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "std::string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::owl::set_string_field
( const std::string& name, const std::string& value )
{
  bool result;

  if ( name == "owl.level" )
    {
      m_level_name = value;
      result = true;
    }
  else
    result = super::set_string_field( name, value );

  return result;
} // owl::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of <std::string>.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::owl::set_string_list_field
( const std::string& name, const std::vector<std::string>& value )
{
  bool result;

  if ( name == "owl.speech.want_an_hazelnut" )
    {
      for(std::size_t i=0; i!=value.size(); ++i)
        if ( !value[i].empty() )
          m_want_hazelnut.push_back( gettext(value[i].c_str()) );
      result = true;
    }
  else if ( name == "owl.speech.happy" )
    {
      for(std::size_t i=0; i!=value.size(); ++i)
        if ( !value[i].empty() )
          m_happy.push_back( gettext(value[i].c_str()) );
      result = true;
    }
  else if ( name == "owl.speech.other_player" )
    {
      for(std::size_t i=0; i!=value.size(); ++i)
        if ( !value[i].empty() )
          m_other_player.push_back( gettext(value[i].c_str()) );
      result = true;
    }
  else if ( name == "owl.speech.already_have" )
    {
      for(std::size_t i=0; i!=value.size(); ++i)
        if ( !value[i].empty() )
          m_already_have.push_back( gettext(value[i].c_str()) );
      result = true;
    }
  else if ( name == "owl.speech.bye" )
    {
      for(std::size_t i=0; i!=value.size(); ++i)
        if ( !value[i].empty() )
          m_goodbye.push_back( gettext(value[i].c_str()) );
      result = true;
    }
  else
    result = super::set_string_list_field( name, value );

  return result;
} // owl::set_string_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activate on with only one player in a two players game.
 * \param p The player activating the owl.
 */
void ptb::owl::on_one_player( const player_proxy& p )
{
  m_activated = true;
  on_found(p.get_index());

  if ( m_has_hazelnut )
    {
      if (m_action == action_idling)
        {
          say( m_already_have );
          start_model_action("speak");
          m_action = action_speaking;
        }
    }
  else if ( m_action == action_idling )
    {
      say( m_other_player );
      start_model_action("speak");
      m_action = action_wait_for_player;
    }
  else
    m_action = action_wait_for_player;
} // owl::on_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activate with all players.
 * \param p1 The first player.
 * \param p2 The second player, in a two players game.
 */
void ptb::owl::on_all_players( const player_proxy& p1, const player_proxy& p2 )
{
  if ( ! level_variables::owl_is_met(get_level()) )
    {
      send_owl_notification(p1.get_index());
      if ( p2 != NULL )
	send_owl_notification(p2.get_index());
    }
    
  level_variables::meet_the_owl(get_level());
  m_activated = true;

  if ( m_has_hazelnut )
    {
      if (m_action == action_idling)
        {
          say( m_already_have );
          start_model_action("speak");
          m_action = action_speaking;
        }
    }
  else if ( m_action != action_start_level_scenario )
    {
      if ( level_variables::get_current_hazelnut(get_level()) )
        {
          say( m_happy );
          start_model_action("speak");
          m_action = action_start_level_scenario;
          m_progress = &owl::progress_ask_hazelnut;

          m_first_player = p1;
          m_second_player = p2;
	  
          m_first_player.set_marionette(true);
          if (p2!=NULL)
	    m_second_player.set_marionette(true);
	}
      else if ( m_action != action_speaking )
        {
          say( m_want_hazelnut );
          start_model_action("speak");
          m_action = action_speaking;
        }
    }
} // owl::on_all_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Keep asking for the hazelnut.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::owl::progress_ask_hazelnut( bear::universe::time_type elapsed_time )
{
  bool ok(false);

  // move the player to face the owl
  if ( !get_rendering_attributes().is_mirrored() )
    {
      if ( m_first_player.get_left() < get_right() + 100)
        m_first_player.do_action(elapsed_time, player_action::move_right);
      else if (m_first_player.get_speed().x == 0)
        {
          ok = true;

          if ( !m_first_player.get_rendering_attributes().is_mirrored() )
            m_first_player.do_action(0.001, player_action::move_left);
        }
    }
  else if ( m_first_player.get_right() > get_left() - 100)
    m_first_player.do_action(elapsed_time, player_action::move_left);
  else if (m_first_player.get_speed().x == 0)
    {
      ok = true;

      if ( m_first_player.get_rendering_attributes().is_mirrored() )
        m_first_player.do_action(0.001, player_action::move_right);
    }

  if ( ok && has_finished_to_speak() )
    {
      start_model_action("idle");
      m_first_player.throw_hazelnut();
      m_progress = NULL;
    }
} // owl::progress_ask_hazelnut()

/*----------------------------------------------------------------------------*/
/**
 * \brief Wait until finised to talk.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::owl::progress_looking_hazelnut
( bear::universe::time_type elapsed_time )
{
  if ( has_finished_to_speak() )
    {
      say( m_goodbye );
      start_model_action("bye");
      m_progress = &owl::progress_start_level;
    }
} // owl::progress_ask_hazelnut()

/*----------------------------------------------------------------------------*/
/**
 * \brief Push the secret level, as soon as the owl stops talking.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::owl::progress_start_level
( bear::universe::time_type elapsed_time )
{
  if ( has_finished_to_speak() )
    {
      m_first_player.set_marionette(false);
      if (m_second_player != NULL)
        m_second_player.set_marionette(false);

      m_progress = NULL;
      start_model_action("idle");

      level_variables::set_secret_level_found(get_level(), true);
      game_variables::set_next_level_name(m_level_name);
      game_variables::set_last_level_exit
        ( m_level_name,  m_first_player.get_index(), PTB_DEFAULT_EXIT_NAME );
      if (m_second_player != NULL)
        game_variables::set_last_level_exit
          ( m_level_name, m_second_player.get_index(), PTB_DEFAULT_EXIT_NAME );
      bear::engine::game::get_instance().push_level( PTB_LOADING_LEVEL_NAME );
    }
} // owl::progress_start_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Collision with an other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::owl::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  hazelnut* a = dynamic_cast<hazelnut*>(&that);

  if ( a != NULL )
    {
      say( m_receive_hazelnut );
      start_model_action("look_hazelnut");
      m_progress = &owl::progress_looking_hazelnut;
      a->kill();
      m_has_hazelnut = true;
    }
} // owl::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the owl talking.
 * \param s The speeches among which we pick a sentence.
 */
void ptb::owl::say( const std::vector<std::string>& s )
{
  std::vector<std::string> speech;

  speech.push_back( s[ (((double)rand() / RAND_MAX) * s.size()) ] );
  speak( s );
} // owl::say()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create level bonus objects.
 */
void ptb::owl::create_level_bonus()
{
  bonus_points* new_bonus_owl = new bonus_points( "Meet the owl", 10000 );

  new_bonus_owl->set_picture_filename("gfx/ui/bonus-icons/bonus-icons.png");
  new_bonus_owl->set_picture_name("owl");
  new_bonus_owl->set_condition
    ( bear::engine::bool_level_variable_getter(&get_level(), "met_the_owl") );

  new_item( *new_bonus_owl );
  CLAW_ASSERT(new_bonus_owl->is_valid(),
              "The bonus_owl isn't correctly initialized" );
  new_bonus_owl->set_center_of_mass(get_center_of_mass());


  bonus_points* new_bonus_secret_level =
    new bonus_points( "Secret level found", 10000 );

  new_bonus_secret_level->set_picture_filename
    ("gfx/ui/bonus-icons/bonus-icons.png");
  new_bonus_secret_level->set_picture_name("owl and hazelnut");
  new_bonus_secret_level->set_condition
    ( bear::engine::bool_level_variable_getter
      (&get_level(), "secret_level_found") );

  new_item( *new_bonus_secret_level );
  CLAW_ASSERT(new_bonus_secret_level->is_valid(),
              "The bonus_secret_level isn't correctly initialized" );
  new_bonus_secret_level->set_center_of_mass(get_center_of_mass());
} // owl::create_level_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send a notification : owl is met.
 * \param index Index of player that met the owl. 
 */
void ptb::owl::send_owl_notification(unsigned int index)
{
  status_layer_notification_message msg;

  bear::visual::sprite sp = 
    get_level_globals().auto_sprite
    ( "gfx/ui/bonus-icons/bonus-icons.png", "owl" );
  msg.set_notification( index, sp, gettext("Meet the owl"));

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // owl::send_owl_notification()
