/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::frog class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/forest/frog.hpp"

#include "ptb/player_proxy.hpp"
#include "ptb/item/floating_score.hpp"

#include "engine/layer/layer.hpp"
#include "engine/world.hpp"
#include "engine/export.hpp"

#include <claw/assert.hpp>

BASE_ITEM_EXPORT( frog, ptb )


/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::frog::frog()
  : sniffable("frog"), 
    m_progress(NULL), m_max_distance(100), m_last_player_index(1)
{
  set_z_fixed(false);
  set_mass(1);
  set_density(2);
  set_friction(0.9);

  set_can_move_items(true);
  set_system_angle_as_visual_angle(true);

  get_rendering_attributes().mirror(false);
} // frog::frog()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::frog::~frog()
{
} // frog::~frog()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::frog::pre_cache()
{
  get_level_globals().load_model("model/forest/frog.cm");
  get_level_globals().load_sound("sound/forest/frog/croak-idle.ogg");
  get_level_globals().load_sound("sound/forest/frog/croak-jump.ogg");
} // frog::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::frog::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/forest/frog.cm") );
  m_initial_position = get_center_of_mass();
  
  choose_idle_action();
  m_progress = &frog::progress_idle;
} // frog::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::frog::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  test_explose();

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // frog::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::frog::set_real_field
( const std::string& name, double value )
{
  bool ok = true;

  if (name == "frog.max_distance")
    m_max_distance = value;
  else
    ok = super::set_real_field(name, value);

  return ok;
} // frog::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_as_train().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::frog::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( info.get_collision_side() == bear::universe::zone::top_zone )
    {
      if ( default_collision(info) )
        {
          player_proxy p(&that);

          if ( p != NULL )
            m_last_player_index = p.get_index();
        }
    }
}// frog::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture filename for counted item class.
 */
std::string ptb::frog::get_picture_filename() const
{
  return "gfx/forest/bonus-icons/bonus-icons.png";
} // frog::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture name for counted item class.
 */
std::string ptb::frog::get_picture_name() const
{
  return "frog";
} // frog::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text for notification.
 */
std::string ptb::frog::get_notification_text() const
{
  return "frog carnage";
} // frog::get_notification_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the number of points of carnage.
 */
unsigned int ptb::frog::get_points() const
{
  return 5000;
} // frog::get_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state idle.
 */
void ptb::frog::progress_idle( bear::universe::time_type elapsed_time )
{
  if ( !test_in_sky() )
    ; // do nothing
} // frog::progress_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state jump.
 */
void ptb::frog::progress_jump( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    if( get_speed().y <= 0 )
      start_model_action("fall");
} // frog::progress_jump()


/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state fall.
 */
void ptb::frog::progress_fall( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    if( get_speed().y >= 0 )
      start_model_action("jump");
} // frog::progress_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state explose.
 */
void ptb::frog::progress_explose( bear::universe::time_type elapsed_time )
{
  // do nothing
} // frog::progress_explose()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start idle state.
 */
void ptb::frog::start_idle()
{
  m_progress = &frog::progress_idle;
} // frog::start_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to jump.
 */
void ptb::frog::start_jump()
{
  m_progress = &frog::progress_jump;
} // frog::start_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to fall.
 */
void ptb::frog::start_fall()
{
  m_progress = &frog::progress_fall;
} // frog::start_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to explose.
 */
void ptb::frog::start_explose()
{
  set_can_move_items(false);
  m_progress = &frog::progress_explose;
  create_floating_score();
  count_me(0);
  on_found(m_last_player_index);
} // frog::start_explose()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply a jump.
 */
void ptb::frog::apply_jump()
{
  if ( get_rendering_attributes().is_mirrored() )
    add_internal_force( bear::universe::force_type(-40000, 50000) );
  else
    add_internal_force( bear::universe::force_type(40000, 50000) );

  start_model_action("jump");
} // frog::apply_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Choose an idle action.
 */
void ptb::frog::choose_idle_action()
{
  std::ostringstream s;
  s << "idle_" << (rand() % 2 + 1);
  start_model_action(s.str());
} // frog::choose_idle_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan if there is a wall in a given direction.
 * \param origin The position from which we start watching.
 * \param dir The direction of the scan.
 */
bool ptb::frog::scan_no_wall_in_direction
( const bear::universe::position_type& origin,
  const bear::universe::vector_type& dir ) const
{
  if ( get_layer().has_world() )
    {
      bear::universe::item_picking_filter filter;
      filter.set_can_move_items_value(true);
      filter.set_forbidden_position(origin);

      return get_layer().get_world().pick_item_in_direction
        (origin, dir, filter) == NULL;
    }
  else
    return false;
} // frog::scan_no_wall_in_direction()

/*---------------------------------------------------------------------------*/
/**
 * \brief Testeif the frog is in the sky and change state thereof.
 *         Return true if the frog is in the sky.
 */
bool ptb::frog::test_in_sky()
{
  bool result = false;

  if ( !has_bottom_contact() )
    {
      result = true;

      if( get_speed().y <= 0 )
        start_model_action("fall");
      else
        start_model_action("jump");
    }

  return result;
} // frog::test_in_sky()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if the frog has bottom contact and change state thereof.
 *         Return true if the frog is now in idle state.
 */
bool ptb::frog::test_bottom_contact()
{
  bool result = false;

  if ( has_bottom_contact() )
    {
      choose_idle_action();
      result = true;
    }

  return result;
} // frog::test_bottom_contact()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if the frog must explose.
 */
void ptb::frog::test_explose()
{
  if ( has_bottom_contact() && has_top_contact() )
    start_model_action("explose");
} // frog::test_explose()

/*----------------------------------------------------------------------------*/
/**
 * \brief The frog try to jump.
 *
 */
void ptb::frog::try_to_jump()
{
  if ( has_bottom_contact() )
    {

      if ( (rand() % 2) == 1)
        get_rendering_attributes().mirror
          (!get_rendering_attributes().is_mirrored());

      if ( can_jump() )
        apply_jump();
      else
        {
          get_rendering_attributes().mirror
            (!get_rendering_attributes().is_mirrored());

          if ( can_jump() )
            apply_jump();
          else
            get_rendering_attributes().mirror
              (!get_rendering_attributes().is_mirrored());
        }
    }
} // frog::try_to_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Test if the frog can jump.
 *
 */
bool ptb::frog::can_jump() const
{
  bool result = true;

  bear::universe::coordinate_type dist;

  dist = m_initial_position.distance(get_center_of_mass());
  if ( dist > m_max_distance )
    {
      if ( get_rendering_attributes().is_mirrored() &&
           (m_initial_position.x > get_center_of_mass().x) )
        result = false;

      if ( !get_rendering_attributes().is_mirrored() &&
           (m_initial_position.x < get_center_of_mass().x) )
        result = false;
    }

  if ( result )
    {
      bear::universe::vector_type dir(150, 0);

      if ( get_rendering_attributes().is_mirrored() )
        dir.x *= -1;

      result = scan_no_wall_in_direction(get_center_of_mass(), dir);
    }

  return result;
} // frog::can_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a floating score.
 */
void ptb::frog::create_floating_score() const
{
  floating_score* s = new floating_score;

  s->set_z_position( super::get_z_position() + 10 );
  s->set_center_of_mass( super::get_center_of_mass() );
  new_item(*s);

  s->add_points( m_last_player_index, 1 );
} // frog::create_floating_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::frog::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::frog, start_idle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::frog, start_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::frog, start_fall, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::frog, start_explose, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::frog, try_to_jump, void );
} // frog::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::frog )
