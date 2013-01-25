/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the hideout_revealing class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/hideout_revealing.hpp"

#include "ptb/util/player_util.hpp"
#include "generic_items/decorative_item.hpp"

BASE_ITEM_EXPORT( hideout_revealing, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::hideout_revealing::hideout_revealing()
  : m_player_in_zone(false), m_definitive_disclosure(false),
    m_revealing_opacity(0), m_hideout_opacity(1),
    m_current_revealed(false), m_last_revealed(false),
    m_hideout_found(false), m_revelation_duration(0.25),
    m_last_modification(0)
{
  set_phantom(true);
  set_can_move_items(false);
} // hideout_revealing::hideout_revealing()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 */
void
ptb::hideout_revealing::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  bool player_in_zone = false;

  if ( !m_current_revealed && !m_hideout_found )
    {
      search_players();

      if ( m_first_player != NULL )
        player_in_zone =
          m_first_player.get_bounding_box().intersects(get_bounding_box());

      if ( !player_in_zone && (m_second_player != NULL) )
        player_in_zone =
          m_second_player.get_bounding_box().intersects(get_bounding_box());

      if ( player_in_zone )
        {
          if ( !m_last_revealed )
            m_last_modification = 0;
          m_current_revealed = true;
          m_hideout_found = m_definitive_disclosure;
        }
    }

  if ( !m_hideout_found )
    {
      if ( !m_current_revealed && m_last_revealed )
        m_last_modification = 0;

      m_last_revealed = m_current_revealed;
      m_current_revealed = false;
    }

  if ( m_last_modification <= m_revelation_duration )
    {
       m_last_modification += elapsed_time;
       if ( player_in_zone || m_hideout_found  )
        reveal();
      else
        hide();
    }
} // hideout_revealing::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::hideout_revealing::build()
{
  super::build();

  search_players();
  m_last_modification = m_revelation_duration;
  hide();
} // hideout_revealing::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of <*base_item>.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::hideout_revealing::set_item_list_field
( const std::string& name, const std::vector<base_item*>& value )
{
  bool result = false;

  if ( name == "hideout_revealing.hiding_items" )
    {
      m_items.clear();
      unsigned int index;
      for ( index = 0; index != value.size(); ++index )
        m_items.push_back(value[index]);
      result = true;
    }
  else
    result = super::set_item_list_field( name, value );

  return result;
} // hideout_revealing::set_item_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c bool.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool
ptb::hideout_revealing::set_bool_field( const std::string& name, bool value )
{
  bool result = false;

  if ( name == "hideout_revealing.definitive_disclosure" )
    {
      m_definitive_disclosure = value;
      result = true;
    }
  else
    result = super::set_bool_field( name, value );

  return result;
} // hideout_revealing::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c double.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::hideout_revealing::set_real_field
( const std::string& name, double value )
{
  bool result = true;

  if ( name == "hideout_revealing.revealing_opacity" )
    m_revealing_opacity = value;
  else if ( name == "hideout_revealing.hideout_opacity" )
    m_hideout_opacity = value;
  else
    result = super::set_real_field( name, value );

  return result;
} // hideout_revealing::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search players.
 */
void ptb::hideout_revealing::search_players()
{
  if ( m_first_player == NULL )
    m_first_player = util::find_player( get_level_globals(), 1 );

  if ( m_second_player == NULL )
    m_second_player = util::find_player( get_level_globals(), 2 );
} // hideout_revealing::search_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Reveal the items.
 */
void ptb::hideout_revealing::reveal()
{
  double opacity
    (m_hideout_opacity + (m_revealing_opacity-m_hideout_opacity) *
     m_last_modification / m_revelation_duration );

  if ( opacity <= 0 )
    opacity = 0;
  else if ( opacity >= 1 )
    opacity = 1;

  std::vector<bear::universe::item_handle>::iterator it;
  for (it = m_items.begin(); it != m_items.end(); ++it)
    {
      if ( *it != NULL )
        {
          bear::decorative_item*
            deco = dynamic_cast<bear::decorative_item*>(it->get());
          if ( deco != NULL )
            deco->get_rendering_attributes().set_opacity(opacity);
        }
    }
} // hideout_revealing::reveal()

/*----------------------------------------------------------------------------*/
/**
 * \brief Hide the items.
 */
void ptb::hideout_revealing::hide()
{
  double opacity =
    m_revealing_opacity + (m_hideout_opacity-m_revealing_opacity) *
    m_last_modification / m_revelation_duration;

  if ( opacity <= 0 )
    opacity = 0;
  else if ( opacity >= 1 )
    opacity = 1;

  std::vector<bear::universe::item_handle>::iterator it;
  for (it = m_items.begin(); it != m_items.end(); ++it)
    {
      if ( *it != NULL )
        {
          bear::decorative_item*
            deco = dynamic_cast<bear::decorative_item*>(it->get());
          if ( deco != NULL )
            deco->get_rendering_attributes().set_opacity( opacity);
        }
    }
} // hideout_revealing::hide()
