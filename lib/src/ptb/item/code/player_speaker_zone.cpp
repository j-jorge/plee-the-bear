/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_speaker_zone class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/player_speaker_zone.hpp"

#include "ptb/controller_config.hpp"
#include "ptb/util/player_util.hpp"

#include "engine/export.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( player_speaker_zone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player_speaker_zone::player_speaker_zone()
  : m_first_player_spoke(false), m_second_player_spoke(false),
    m_first_player_in_zone(false), m_second_player_in_zone(false)
{
  set_phantom(true);
  set_can_move_items(false);
} // player_speaker_zone::player_speaker_zone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player_speaker_zone::progress
( bear::universe::time_type elapsed_time )
{
  search_players();

  if ( m_first_player != NULL )
    test_player_enter(m_first_player, m_first_player_in_zone);

  if ( m_second_player != NULL )
    test_player_enter(m_second_player, m_second_player_in_zone);
} // player_speaker_zone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of <std::string>.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::player_speaker_zone::set_string_list_field
( const std::string& name, const std::vector<std::string>& value )
{
  bool result = false;

  if ( name == "player_speaker_zone.speeches" )
    {
      m_speeches.resize(value.size());

      for (std::size_t i=0; i!=value.size(); ++i)
        m_speeches[i] = gettext(value[i].c_str());

      result = true;
    }
  else
    result = super::set_string_list_field( name, value );

  return result;
} // player_speaker_zone::set_string_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::player_speaker_zone::is_valid() const
{
  return !m_speeches.empty() && super::is_valid();
} // player_speaker_zone::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search players.
 */
void ptb::player_speaker_zone::search_players()
{
  if ( m_first_player == NULL )
    m_first_player = util::find_player( get_level_globals(), 1 );

  if ( m_second_player == NULL )
    m_second_player = util::find_player( get_level_globals(), 2 );
} // player_speaker_zone::search_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Test if a player enter in the zone.
 */
void ptb::player_speaker_zone::test_player_enter
( const player_proxy& p, bool& player_in_zone )
{
  bear::universe::rectangle_type bounding_box_1( p.get_bounding_box() );

  if ( bounding_box_1.intersects(get_bounding_box()) )
    {
      if ( !player_in_zone )
        {
           if ( p.has_finished_to_speak() )
             {
               controller_config cfg;
               const controller_layout* layout(NULL);
               if ( p.get_index() <= 2)
                 layout = &(cfg.get_layout( p.get_index() ));

               std::vector<std::string> speeches;
               std::vector<std::string>::iterator it;
               for ( it=m_speeches.begin(); it!=m_speeches.end(); ++it)
                 {
                   std::string text;
                   if ( layout != NULL )
                     layout->escape_action_sequence(*it, text);
                   else
                     text = *it;

                   speeches.push_back(text);
                 }

               p.speak(speeches);
             }

           player_in_zone = true;
        }
    }
  else
    player_in_zone = false;
} // player_speaker_zone::test_player_enter()
