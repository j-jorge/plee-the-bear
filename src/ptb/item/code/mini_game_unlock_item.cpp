/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::mini_game_unlock_item class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/mini_game_unlock_item.hpp"

#include "ptb/game_variables.hpp"
#include "generic_items/decorative_item.hpp"
#include "visual/scene_writing.hpp"
#include "visual/scene_polygon.hpp"
#include "visual/scene_rectangle.hpp"

BASE_ITEM_EXPORT( mini_game_unlock_item, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is well initialized.
 */
bool ptb::mini_game_unlock_item::is_valid() const
{
  return !m_mini_game_name.empty() && super::is_valid();
} // mini_game_unlock_item::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::mini_game_unlock_item::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "mini_game_unlock_item.name" )
    m_mini_game_name = value;
  else if ( name == "mini_game_unlock_item.unlocked_sentence" )
    m_unlocked_sentence = value;
  else
    result = super::set_string_field(name, value);

  return result;
} // mini_game_unlock_item::set_string_field()

/*---------------------------------------------------------------------------*/
/**
 * \brief This method is called when the toggle switches on.
 * \param activator The item that activates the toggle, if any.
 */
void ptb::mini_game_unlock_item::on_toggle_on(base_item* activator)
{
  super::on_toggle_on(activator);

  game_variables::set_mini_game_status(m_mini_game_name, true);
  game_variables::set_current_level_mini_game_state(true);

  create_text_decoration();
} // mini_game_unlock_item::on_toggle_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprites representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void ptb::mini_game_unlock_item::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  super::get_visual(visuals);

  if ( !this->get_text().empty() )
    {
      bear::visual::scene_writing e( 0, 0, this->get_writing() );
      e.set_scale_factor
        ( get_width() / get_writing().get_width(),
          get_height() / get_writing().get_height() );

      std::vector<bear::universe::position_type> points;
      points.push_back(bear::universe::position_type(-10, -10));
      points.push_back
        (bear::universe::position_type(get_writing().get_width()+10, -10));
      points.push_back
        (bear::universe::position_type(get_writing().get_width()+10,
                                       get_writing().get_height()+10));
      points.push_back
        (bear::universe::position_type(-10, get_writing().get_height()+10));

      bear::universe::rectangle_type rect(points[0], points[2]);

      bear::visual::scene_element e1
        (bear::visual::scene_rectangle
         (get_left(), get_bottom(),
          claw::graphic::yellow_pixel, rect, false));

      bear::visual::scene_element e2
        (bear::visual::scene_polygon(get_left(), get_bottom(),
                                     claw::graphic::black_pixel, points ));
      e2.get_rendering_attributes().set_opacity(0.3);

      add_visual( e, visuals );
      visuals.push_front(e1);
      visuals.push_front(e2);
    }
} // mini_game_unlock_item::get_visual()

/*---------------------------------------------------------------------------*/
/**
 * \brief Create the decoration that indicates the unlocked mini-game.
 */
void ptb::mini_game_unlock_item::create_text_decoration()
{
  if ( m_unlocked_sentence.empty() )
    return;

  set_center_of_mass(get_center_of_mass());

  set_font(get_level_globals().get_font("font/fixed_yellow-10x20.fnt", 20));
  set_text(gettext(m_unlocked_sentence.c_str()));
  refresh_writing();
  set_size( get_writing().get_size() );
} // mini_game_unlock_item::create_text_decoration()
