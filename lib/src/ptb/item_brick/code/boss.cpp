/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::boss class.
 * \author Julien Jorge
 */
#include "ptb/item_brick/boss.hpp"

#include "ptb/defines.hpp"
#include "ptb/message/status_layer_boss_message.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/item/floating_score.hpp"
#include "ptb/item/bonus_points/bonus_boss.hpp"
#include "ptb/util/player_util.hpp"

#include "generic_items/camera_shaker.hpp"
#include "generic_items/decorative_effect.hpp"
#include "generic_items/star.hpp"

#include "engine/export.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::boss::boss()
  : m_progress(NULL), m_godify_duration(0), m_music_id(0)
{

} // boss::boss()

/*---------------------------------------------------------------------------*/
/**
 * \brief Load the ressources required by the item.
 */
void ptb::boss::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_sound("music/boss.ogg");
  get_level_globals().load_sound("sound/effect/earthquake.ogg");
} // boss::pre_cache()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::boss::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);

  if ( m_godify_duration > 0 )
    {
      m_godify_duration -= elapsed_time;
      get_rendering_attributes().set_intensity(0, 0, 0);
    }
  else if ( m_godify_duration < 0 )
    {
      get_rendering_attributes().set_intensity(1, 1, 1);
      m_godify_duration = 0;
    }
} // boss::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::boss::on_enters_layer()
{
  super::on_enters_layer();

  bonus_boss* new_bonus_boss = new bonus_boss();

  new_bonus_boss->set_picture_filename(get_bonus_picture_filename());
  new_bonus_boss->set_picture_name(get_bonus_picture_name());

  new_item( *new_bonus_boss );
  CLAW_ASSERT(new_bonus_boss->is_valid(),
              "The bonus_boss isn't correctly initialized" );
  new_bonus_boss->set_center_of_mass(get_center_of_mass());
} // boss::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type item
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::boss::set_item_field( const std::string& name, base_item* value)
{
  bool result(true);

  if ( name == "boss.on_dead" )
    {
      m_toggle = value;
      result = m_toggle != (bear::engine::with_toggle*)NULL;
    }
  else
    result = super::set_item_field(name, value);

  return result;
} // boss::set_item_field()

/*---------------------------------------------------------------------------*/
/**
 * \brief Corrupt the boss.
 * \param amount The amount of corruption.
 */
void ptb::boss::corrupt( double amount )
{
  set_max_energy( std::max( 0.0, get_max_energy() - amount ) );
} // boss::corrupt()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::boss::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{

} // boss::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the boss die.
 */
void ptb::boss::inform_dead()
{
  get_level_globals().stop_music(m_music_id);

  game_variables::set_current_level_boss_killed(true);

  if ( m_toggle != (bear::engine::with_toggle*)NULL )
    m_toggle->toggle_on(this);
} // boss::inform_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the floating score for a player.
 * \param p1_mark The name of the mark in the model where the score is created
 *        for the first player.
 * \param p2_mark The name of the mark in the model where the score is created
 *        for the second player.
 */
void ptb::boss::create_floating_score
( const std::string& p1_mark, const std::string& p2_mark ) const
{
  create_floating_score(1, get_mark_world_position(p1_mark));
  create_floating_score(2, get_mark_world_position(p2_mark));
} // boss::create_floating_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the floating score for a player.
 * \param index The index of the player.
 * \param pos The position of the score.
 */
void ptb::boss::create_floating_score
( unsigned int index, const bear::universe::position_type& pos ) const
{
  const player_proxy p( util::find_player( get_level_globals(), index ) );

  if ( p == NULL )
    return;

  const unsigned int points(30000);
  floating_score* s = new floating_score;

  s->set_z_position( get_z_position() + 10 );
  s->set_center_of_mass( pos );
  new_item(*s);

  s->add_points( index, points );
} // boss::create_floating_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress when increasing the energy.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::boss::progress_energy( bear::universe::time_type elapsed_time )
{
  const double e = get_energy() + m_energy_increment * elapsed_time;
  set_max_energy( e );
  set_energy( e );

  m_action_duration = std::max(0.0, m_action_duration - elapsed_time);

  if ( m_action_duration == 0 )
    m_progress = NULL;
} // boss::progress_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply an effect to show that the rabbit is being transformed by the
 *        power of god.
 * \param d The duration of the effect.
 * \param size The size of the star behind the rabbit.
 */
void ptb::boss::godify
( bear::universe::time_type d, bear::visual::size_type size )
{
  if ( m_music_id == 0 )
    m_music_id = get_level_globals().play_music("music/boss.ogg", 0);

  bear::star* s = new bear::star
    ( 10, 0.75, PTB_GOD_AURA_COLOR, 2, PTB_GOD_AURA_BORDER_COLOR );
  s->set_size(size, size);

  s->set_z_position(get_z_position() - 1);
  new_item( *s );
  s->set_center_of_mass(get_center_of_mass());

  bear::decorative_effect* decoration_effect = new bear::decorative_effect;

  decoration_effect->set_duration(d);
  decoration_effect->set_size_factor(0.5, 4);
  decoration_effect->set_angle_offset(0, 3.14159);
  decoration_effect->set_item(s, true);

  new_item( *decoration_effect );

  m_godify_duration = d;

  bear::camera_shaker::shake_around
    ( *this, 15, 1,
      get_level_globals().new_sample("sound/effect/earthquake.ogg") );
} // boss::godify()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the energy of the rabbit in the status layer.
 * \param d The duration of the increase.
 */
void ptb::boss::show_energy( bear::universe::time_type d )
{
  m_progress = &boss::progress_energy;
  m_action_duration = d;
  m_energy_increment = get_max_energy() / d;

  set_max_energy(0);
  set_energy(0);

  status_layer_boss_message msg;
  msg.set_boss(this);

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // boss::show_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::boss::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_2
    ( boss, godify, void, bear::universe::time_type,
      bear::visual::size_type );
  TEXT_INTERFACE_CONNECT_METHOD_1
    ( boss, show_energy, void, bear::universe::time_type );
} // boss::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::boss )
