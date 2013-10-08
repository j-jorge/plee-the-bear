/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::god class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/god.hpp"

#include "universe/forced_movement/forced_translation.hpp"
#include "generic_items/decorative_item.hpp"
#include "generic_items/delayed_kill_item.hpp"

#include "ptb/util/player_util.hpp"

BASE_ITEM_EXPORT( god, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::god::god()
  : m_progress(&god::progress_idle)
{
  set_mass(100);
  set_density(2);

  m_monster_type = monster::nature_monster;
  m_energy = 1;
  m_offensive_phase = false;
} // god::god()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::god::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // god::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::god::pre_cache()
{
  // model
  get_level_globals().load_model("model/god.cm");
} // god::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void ptb::god::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/god.cm") );

  start_model_action("invisible");
} // god::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Launch the ball toward the players.
 * \param d The duration of the movement to reach the players.
 * \param t The duration after which the ball disappear.
 */
void ptb::god::launch_ball
( bear::universe::time_type d, bear::universe::time_type t )
{
  bear::engine::model_mark_placement m;
  player_proxy p = util::find_player(get_level_globals(), 1);

  if ( p == NULL )
    p = util::find_player(get_level_globals(), 2);

  if ( (p == NULL) || !get_mark_placement("ball", m) )
    return;

  bear::decorative_item* item = new bear::decorative_item();
  item->set_animation
    ( *get_current_action()->get_mark("ball").get_animation() );

  new_item(*item);
  item->set_center_of_mass(m.get_position());
  item->set_size(m.get_size());
  item->set_forced_movement
    ( bear::universe::forced_translation
      ( (p.get_center_of_mass() - m.get_position()) / d, t ) );

  bear::delayed_kill_item* killer = new bear::delayed_kill_item();
  killer->add_item(item);
  killer->set_duration(t);
  new_item(*killer);

  start_model_action("idle");
} // god::launch_ball()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state idle.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::god::progress_idle
( bear::universe::time_type elapsed_time )
{
  // do nothing
} // god::progress_idle()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state talk.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::god::progress_talk
( bear::universe::time_type elapsed_time )
{
  if ( has_finished_to_speak() && (get_current_action_name() == "talk") )
    start_model_action("idle");
} // god::progress_talk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of the state idle.
 */
void ptb::god::start_idle()
{
  m_progress = &god::progress_idle;
} // god::start_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of the state talk.
 */
void ptb::god::start_talk()
{
  m_progress = &god::progress_talk;
} // god::start_talk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do an action.
 * \param a The action to do.
 */
void ptb::god::do_action(const std::string& a)
{
  start_model_action(a);
} // god::do_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief God say a sentence.
 * \param speech The speech.
 */
void ptb::god::talk(const std::vector<std::string>& speech)
{
  start_model_action("talk");

  std::vector<std::string> speeches;

  for (unsigned int i=0; i != speech.size(); ++i )
    speeches.push_back(gettext(speech[i].c_str()));

  speak(speeches);
} // god::talk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::god::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( god, start_idle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( god, start_talk, void );
  TEXT_INTERFACE_CONNECT_METHOD_2
    ( god, launch_ball, void, bear::universe::time_type,
      bear::universe::time_type );
  TEXT_INTERFACE_CONNECT_METHOD_1
    ( god, do_action, void, const std::string& );
  TEXT_INTERFACE_CONNECT_METHOD_1
    ( god, talk, void, const std::vector<std::string>& );
} // god::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::god )
