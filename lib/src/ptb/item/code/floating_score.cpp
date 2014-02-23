/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::floating_score class.
 * \author Julien Jorge
 */
#include "ptb/item/floating_score.hpp"

#include "generic_items/delayed_kill_item.hpp"
#include "generic_items/star.hpp"
#include "generic_items/tweener_item.hpp"
#include "generic_items/delayed_kill_item.hpp"
#include "universe/forced_movement/forced_tracking.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/util/player_util.hpp"

#include <boost/bind.hpp>
#include <claw/tween/easing/easing_linear.hpp>

#include <sstream>
#include <limits>

BASE_ITEM_EXPORT( floating_score, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::floating_score::floating_score()
{
  set_kill_when_leaving(true);
} // floating_score::floating_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::floating_score::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_font("font/lobster.otf");
} // floating_score::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::floating_score::build()
{
  super::build();

  set_font( get_level_globals().get_font("font/lobster.otf", 30) );
} // floating_score::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the score given by the item.
 * \param player_index The index of the player to which the points are given.
 * \param points The points to give to the player.
 * \param display_star Tell if we display a star.
 */
void ptb::floating_score::add_points
( unsigned int player_index, unsigned int points, bool display_star )
{
  const unsigned int old_score( game_variables::get_score(player_index) );
  const unsigned int new_score( old_score + points );

  game_variables::set_score( player_index, new_score );

  // check if the player wins a new try
  if ( (old_score / PTB_ONE_UP_POINTS_COUNT)
       < (new_score / PTB_ONE_UP_POINTS_COUNT) )
    give_one_up_to(player_index);

  const double intensity( (double)points / (double)PTB_MAX_POINTS_AT_ONCE );

  if ( player_index == 1 )
    get_rendering_attributes().set_intensity(intensity, 1, intensity);
  else
    get_rendering_attributes().set_intensity(intensity, intensity, 1);

  std::ostringstream oss;
  oss << points;
  set_text( oss.str() );

  create_effect(this);

  if ( display_star )
    create_star();
} // floating_score::add_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give one more try to a player.
 * \param player_index The index of the player to which the points are given.
 */
void ptb::floating_score::one_up( unsigned int player_index )
{
  game_variables::set_lives_count
    ( player_index, game_variables::get_lives_count(player_index) + 1);

  if ( player_index == 1 )
    get_rendering_attributes().set_intensity(1, 0, 0);
  else
    get_rendering_attributes().set_intensity(0, 1, 1);

  set_text( "1up" );

  create_effect(this);

  get_level_globals().play_music("music/1-up.ogg", 1);
} // floating_score::one_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the displayed text.
 * \param text The text to display.
 */
void ptb::floating_score::set_score( const std::string& text )
{
  set_text( text );

  create_effect(this);
} // floating_score::set_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the effects on the score.
 */
void ptb::floating_score::create_effect(bear::engine::base_item* item)
{
  const bear::universe::position_type pos(get_center_of_mass());
  fit_to_text();
  set_center_of_mass(pos);
  get_rendering_attributes().set_size( get_size() / 2 );

  bear::delayed_kill_item* killer = new bear::delayed_kill_item;

  killer->set_duration(1);
  killer->add_item(item);

  new_item(*killer);
} // floating_score::create_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a one up to a player, creating a new floating_score on him.
 * \param player_index The index of the player to which the points are given.
 */
void ptb::floating_score::give_one_up_to( unsigned int player_index ) const
{
  player_proxy p = util::find_player( get_level_globals(), player_index );

  if ( p != NULL )
    p.give_one_up();
} // floating_score::give_one_up_to()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a star behing the cart.
 */
void ptb::floating_score::create_star()
{
  bear::star* s =
    new bear::star
    ( 15, 1, bear::visual::color(255, 21, 21), 3,
      bear::visual::color(255, 235, 7) );

  s->set_size(200, 100);
  s->set_z_position( get_z_position() - 1 );
  s->set_center_of_mass(get_center_of_mass());
  s->set_ratio( 0.75 );

  new_item(*s);
  
  create_effect(s);
} // floating_score::create_star()
