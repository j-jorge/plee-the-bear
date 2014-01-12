/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::power_effect class.
 * \author Julien Jorge
 */
#include "ptb/item/power_effect.hpp"

#include "ptb/game_variables.hpp"

#include "generic_items/decorative_effect.hpp"
#include "generic_items/decorative_item.hpp"
#include "generic_items/star.hpp"

#include "engine/game.hpp"
#include "universe/forced_movement/forced_tracking.hpp"

#include <boost/bind.hpp>

BASE_ITEM_EXPORT( power_effect, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::power_effect::power_effect()
: m_air(NULL), m_fire(NULL), m_water(NULL)
{
  set_phantom(true);
  set_can_move_items(false);
  set_artificial(true);

  set_mass(1);

} // power_effect::power_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the resources required by this item.
 */
void ptb::power_effect::pre_cache()
{
  get_level_globals().load_animation("animation/effect/power/air_effect.canim");
  get_level_globals().load_animation
    ("animation/effect/power/fire_effect.canim");
  get_level_globals().load_animation
    ("animation/effect/power/water_effect.canim");
} // power_effect::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the player whose powers are displayed.
 * \param i The index of the player.
 */
void ptb::power_effect::set_player_index( unsigned int i )
{
  m_signals.clear();

  remove_air_effect();
  remove_fire_effect();
  remove_water_effect();

  if ( game_variables::get_air_power(i) )
    add_air_effect();

  if ( game_variables::get_fire_power(i) )
    add_fire_effect();

  if ( game_variables::get_water_power(i) )
    add_water_effect();

  connect
    ( bear::engine::game::get_instance().listen_bool_variable_change
      ( game_variables::get_air_power_variable_name(i),
        boost::bind( &power_effect::on_air_power_changed, this, _1) ) );

  connect
    ( bear::engine::game::get_instance().listen_bool_variable_change
      ( game_variables::get_fire_power_variable_name(i),
        boost::bind( &power_effect::on_fire_power_changed, this, _1) ) );

  connect
    ( bear::engine::game::get_instance().listen_bool_variable_change
      ( game_variables::get_water_power_variable_name(i),
        boost::bind( &power_effect::on_water_power_changed, this, _1) ) );
} // power_effect::set_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the items whose progress depends upon *this.
 * \param d (out) The items.
 */
void ptb::power_effect::get_dependent_items
( bear::universe::physical_item::item_list& d ) const
{
  if ( m_air != NULL )
    d.push_back(m_air);

  if ( m_fire != NULL )
    d.push_back(m_fire);

  if ( m_water != NULL )
    d.push_back(m_water);
} // power_effect::get_dependent_items()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a connection to a boost::signals instance.
 * \param c The connection to follow.
 */
void ptb::power_effect::connect( const boost::signals::connection& c )
{
  m_signals.push_back( new boost::signals::scoped_connection(c) );
} // power_effect::connect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of displayed powers.
 */
std::size_t ptb::power_effect::get_powers_count() const
{
  std::size_t result(0);

  if ( m_air != NULL )
    ++result;

  if ( m_fire != NULL )
    ++result;

  if ( m_water != NULL )
    ++result;

  return result;
} // power_effect::get_powers_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the item representing a given power.
 * \param anim The animation of the power.
 */
bear::engine::base_item*
ptb::power_effect::create_power_item( const std::string& anim ) const
{
  bear::decorative_item* result = new bear::decorative_item();
  bear::visual::animation a = get_level_globals().get_animation(anim);

  a.set_angle(3.14159 / 2);

  result->set_animation(a);
  result->set_system_angle_as_visual_angle(true);
  result->set_mass(1);
  result->set_center_of_mass( get_center_of_mass() );

  new_item(*result);

  return result;
} // power_effect::create_power_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the item representing a new power.
 * \param fill_color The color inside the effect.
 * \param border_color The color of the border of the effect.
 */
void ptb::power_effect::show_change_effect
( const bear::visual::color& fill_color,
  const bear::visual::color& border_color )
{
  bear::star* new_decoration =
    new bear::star( 16, 1, border_color, 2, fill_color );

  new_decoration->set_z_position(get_z_position() - 10);
  new_decoration->set_size( 160, 160 );
  new_item( *new_decoration );
  new_decoration->set_center_of_mass(get_center_of_mass());

  const bear::universe::time_type d(0.5);
  bear::universe::forced_tracking mvt(d);
  mvt.set_reference_point_on_center( *this );
  new_decoration->set_forced_movement(mvt);

  bear::decorative_effect* decoration_effect = new bear::decorative_effect;

  decoration_effect->set_duration(d);
  bear::visual::color init_color, end_color;
  init_color.set(1,1,1,1);
  end_color.set(1,1,1,0);
  decoration_effect->set_color( init_color, end_color );
  decoration_effect->set_item(new_decoration, true);

  new_item( *decoration_effect );
} // power_effect::show_change_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the forced movement to the item representing a power.
 * \param item The item.
 */
void ptb::power_effect::apply_movement( bear::engine::base_item& item )
{
  switch ( get_powers_count() )
    {
    case 0: apply_movement_1(item); break;
    case 1: apply_movement_2(item); break;
    case 2: apply_movement_3(item); break;
    default:
      { CLAW_FAIL("To many powers for the effect."); }
    }
} // power_effect::apply_movement()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the forced movement to the item representing a power for the
 *        case where there is a single power.
 * \param item The item for the single power.
 */
void ptb::power_effect::apply_movement_1( bear::engine::base_item& item )
{
  bear::universe::forced_rotation f( create_forced_movement() );

  f.set_start_angle(0);
  f.set_end_angle(2 * 3.14159);

  item.set_forced_movement(f);
} // power_effect::apply_movement_1()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the forced movement to the item representing a power for the
 *        case where there are two power.
 * \param item The item for the second power.
 */
void ptb::power_effect::apply_movement_2( bear::engine::base_item& item )
{
  bear::universe::forced_rotation f( create_forced_movement() );

  const double a =
    3.14159
    + get_center_of_mass().slope_angle
    ( get_first_power()->get_center_of_mass() );

  f.set_start_angle(a);
  f.set_end_angle(a + 2 * 3.14159);

  item.set_forced_movement(f);
} // power_effect::apply_movement_2()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the forced movement to the items representing a power for the
 *        case where there are three power.
 * \param item The item for the third power.
 */
void ptb::power_effect::apply_movement_3( bear::engine::base_item& item )
{
  bear::universe::forced_rotation f( create_forced_movement() );

  const double ref_angle =
    get_center_of_mass().slope_angle
    ( get_first_power()->get_center_of_mass() );

  double a = ref_angle - 2 * 3.14159 / 3;

  f.set_start_angle(a);
  f.set_end_angle(a + 2 * 3.14159);

  item.set_forced_movement(f);

  a = ref_angle + 2 * 3.14159 / 3;

  f.set_start_angle(a);
  f.set_end_angle(a + 2 * 3.14159);

  get_second_power()->set_forced_movement(f);
} // power_effect::apply_movement_3()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the first power among the ones displayed.
 */
bear::engine::base_item* ptb::power_effect::get_first_power() const
{
  if ( m_air != NULL )
    return m_air;

  if ( m_fire != NULL )
    return m_fire;

  if ( m_water != NULL )
    return m_water;

  return NULL;
} // power_effect::get_first_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the second power among the ones displayed.
 */
bear::engine::base_item* ptb::power_effect::get_second_power() const
{
  if ( m_air != NULL )
    {
      if ( m_fire != NULL )
        return m_fire;

      if ( m_water != NULL )
        return m_water;
    }

  if ( (m_fire != NULL) && (m_water != NULL) )
    return m_water;

  return NULL;
} // power_effect::get_second_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the default forced movement for the effect of a power.
 */
bear::universe::forced_rotation ptb::power_effect::create_forced_movement()
{
  bear::universe::forced_rotation f;

  f.set_radius(80);
  f.set_total_time(2);
  f.set_reference_point_on_center(*this);
  f.set_acceleration_time(0);
  f.set_angle_application( bear::universe::forced_rotation::apply_force );

  return f;
} // power_effect::create_forced_movement()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add the effect representing the power of air.
 */
void ptb::power_effect::add_air_effect()
{
  remove_air_effect();

  bear::engine::base_item* result =
    create_power_item("animation/effect/power/air_effect.canim");
  apply_movement(*result);
  m_air = result;
} // power_effect::add_air_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove the effect representing the power of air.
 */
void ptb::power_effect::remove_air_effect()
{
  if ( m_air != NULL )
    {
      m_air->kill();
      m_air = NULL;
    }
} // power_effect::remove_air_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add the effect representing the power of fire.
 */
void ptb::power_effect::add_fire_effect()
{
  remove_fire_effect();

  bear::engine::base_item* result =
    create_power_item("animation/effect/power/fire_effect.canim");
  apply_movement(*result);
  m_fire = result;
} // power_effect::add_fire_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove the effect representing the power of fire.
 */
void ptb::power_effect::remove_fire_effect()
{
  if ( m_fire != NULL )
    {
      m_fire->kill();
      m_fire = NULL;
    }
} // power_effect::remove_fire_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add the effect representing the power of water.
 */
void ptb::power_effect::add_water_effect()
{
  remove_water_effect();

  bear::engine::base_item* result =
    create_power_item("animation/effect/power/water_effect.canim");
  apply_movement(*result);
  m_water = result;
} // power_effect::add_water_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove the effect representing the power of water.
 */
void ptb::power_effect::remove_water_effect()
{
  if ( m_water != NULL )
    {
      m_water->kill();
      m_water = NULL;
    }
} // power_effect::remove_water_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief The state of the air power has changed.
 * \param v The new value of the game variable.
 */
void ptb::power_effect::on_air_power_changed( bool v )
{
  if ( v )
    {
      add_air_effect();
      show_change_effect
        ( bear::visual::color(200, 200, 200), claw::graphic::white_pixel );
    }
  else
    remove_air_effect();
} // power_effect::on_air_power_changed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The state of the fire power has changed.
 * \param v The new value of the game variable.
 */
void ptb::power_effect::on_fire_power_changed( bool v )
{
  if ( v )
    {
      add_fire_effect();
      show_change_effect
        ( bear::visual::color(200, 0, 0), claw::graphic::red_pixel );
    }
  else
    remove_fire_effect();
} // power_effect::on_fire_power_changed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The state of the water power has changed.
 * \param v The new value of the game variable.
 */
void ptb::power_effect::on_water_power_changed( bool v )
{
  if ( v )
    {
      add_water_effect();
      show_change_effect
        ( bear::visual::color(0, 100, 200), claw::graphic::cyan_pixel );
    }
  else
    remove_water_effect();
} // power_effect::on_water_power_changed()
