/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_box class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_box.hpp"

#include "ptb/item/bonus_points/bonus_all_dead.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/player_proxy.hpp"
#include "ptb/util/player_util.hpp"

#include "universe/collision_info.hpp"

#include "generic_items/decorative_item.hpp"
#include "generic_items/decorative_effect.hpp"

#include "engine/game.hpp"
#include "engine/world.hpp"
#include "engine/layer/layer.hpp"
#include "engine/export.hpp"

BASE_ITEM_EXPORT( bonus_box, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::bonus_box::pre_cache()
{
  super::pre_cache();

  // The little Plee
  get_level_globals().load_model("model/little_plee.cm");

  get_level_globals().load_animation("animation/powerup/fire.canim");
  get_level_globals().load_animation("animation/powerup/air.canim");
  get_level_globals().load_animation("animation/powerup/water.canim");
  get_level_globals().load_animation("animation/powerup/invincibility.canim");
  get_level_globals().load_animation("animation/powerup/stones_stock.canim");
  get_level_globals().load_animation
    ("animation/powerup/stones_big_stock.canim");
  get_level_globals().load_animation("animation/powerup/one_more_life.canim");
  get_level_globals().load_animation
    ("animation/powerup/increase_max_energy.canim");
  get_level_globals().load_animation
    ("animation/powerup/increase_max_energy-alt.canim");
  //get_level_globals().load_animation
  //  ("animation/powerup/switch_players.canim");

  get_level_globals().load_animation("animation/powerup/small_air.canim");
  get_level_globals().load_animation("animation/powerup/small_fire.canim");
  get_level_globals().load_animation("animation/powerup/small_water.canim");
  get_level_globals().load_animation( "animation/stones/stone.canim" );

  get_level_globals().load_image("gfx/bonus-box-2.png");
} // bonus_box::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_box::build()
{
  super::build();
  
  set_size( 50, 80 );
  set_gap_x(-5);
} // bonus_box::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture filename for counted item class.
 */
std::string ptb::bonus_box::get_picture_filename() const
{
  return "gfx/ui/bonus-icons/bonus-icons.png";
} // bonus::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture name for counted item class.
 */
std::string ptb::bonus_box::get_picture_name() const
{
  return "bonus boxes";
} // bonus_box::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text for notification.
 */
std::string ptb::bonus_box::get_notification_text() const
{
  return "All bonus boxes";
} // bonus_box::get_notification_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the number of points of carnage.
 */
unsigned int ptb::bonus_box::get_points() const
{
  return 5000;
} // bonus_box::get_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::bonus_box::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    {
      if ( !get_bonus_given()
           && ( ( info.get_collision_side()
                  == bear::universe::zone::middle_left_zone ) ||
                ( info.get_collision_side()
                  == bear::universe::zone::middle_right_zone ) )
           && p.is_in_offensive_phase() )
        {
	  player_proxy pl;
	  if ( get_player_index() != 0 ) 
	    pl = util::find_player( get_level_globals(), get_player_index() );
	  else
	    pl = p;

	  if ( pl != NULL )
	    {
	      count_me(pl.get_index());
	      give_bonus(pl);
	      create_broken_bonus_box();
	      create_broken_glass(p.get_rendering_attributes().is_mirrored());
	      create_honeypot_decoration();
	  
	      if ( ( ( p.get_index() == 1) && ( get_player_index() == 2 ) ) ||
		   ( ( p.get_index() == 2) && ( get_player_index() == 1 ) ) )
		send_thief_notification(p.get_index());
	    }	  
        }
      else
        default_collision(info);
    }
  else
    default_collision(info);
} // bonus_box::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::bonus_box::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // bonus_box::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration of a broken bonus_box.
 */
void ptb::bonus_box::create_broken_bonus_box()
{
   bear::decorative_item* item = new bear::decorative_item;

   item->set_sprite
     ( get_level_globals().auto_sprite
       ( "gfx/bonus-box-2.png", "broken box bottom" ) );
   item->set_z_position(get_z_position());
   item->set_mass(get_mass());
   item->get_rendering_attributes().mirror
     (get_rendering_attributes().is_mirrored());
   item->get_rendering_attributes().flip
     (get_rendering_attributes().is_flipped());
   item->set_density(get_density());
   item->set_phantom(false);
   item->set_artificial(false);
   new_item( *item );

   if ( get_rendering_attributes().is_flipped() )
     item->set_top_middle(get_top_middle());
   else
     item->set_bottom_middle(get_bottom_middle());

   CLAW_ASSERT
     ( item->is_valid(),
       "The decoration of broken bonus_box isn't correctly initialized" );
} // bonus_box::create_broken_bonus_box()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration of a broken glass.
 * \param left_orientation Indicates if the glass go on the left.
 */
void ptb::bonus_box::create_broken_glass(bool left_orientation)
{
  bear::decorative_item* item = new bear::decorative_item;

  item->set_sprite
     ( get_level_globals().auto_sprite
       ( "gfx/bonus-box-2.png", "broken box top" ) );
  item->get_rendering_attributes().set_angle(get_visual_angle());
  item->set_z_position(get_z_position());
  item->set_mass(5);
  item->get_rendering_attributes().mirror
     (get_rendering_attributes().is_mirrored());
  item->get_rendering_attributes().flip
     (get_rendering_attributes().is_flipped());
  item->set_density(2);
  item->set_phantom(false);
  item->set_artificial(false);
  item->set_size( 50, 48 );

  bear::universe::force_type force(93750, 18750);
  if ( left_orientation )
    force.x *= -1;

  double a = (1.0 * rand() / RAND_MAX)+0.5;
  item->add_internal_force(force*a);

  new_item( *item );

  if ( get_rendering_attributes().is_flipped() )
     item->set_bottom_middle(get_bottom_middle());
  else
    item->set_top_middle(get_top_middle());



  CLAW_ASSERT( item->is_valid(),
         "The decoration of broken glass isn't correctly initialized" );
} // bonus_box::create_broken_glass()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do the actions related to a change in the bonus type.
 * \param t The new type of the bonus.
 */
void ptb::bonus_box::do_set_type(base_bonus_type t)
{
  switch(t)
    {
    case fire_power:
      set_animation
        ( get_level_globals().get_animation("animation/powerup/fire.canim") );
      break;
    case air_power:
      set_animation
        ( get_level_globals().get_animation("animation/powerup/air.canim") );
      break;
    case water_power:
      set_animation
        ( get_level_globals().get_animation("animation/powerup/water.canim") );
      break;
    case invincibility_power:
      set_animation( get_level_globals().get_animation
                     ("animation/powerup/invincibility.canim") );
      break;
    case stones_stock:
      set_animation( get_level_globals().get_animation
                     ("animation/powerup/stones_stock.canim") );
      set_stock(20);
      break;
    case stones_big_stock:
      set_animation( get_level_globals().get_animation
                     ("animation/powerup/stones_big_stock.canim") );
      set_stock(50);
      break;
    case one_more_life:
      set_animation( get_level_globals().get_animation
                     ("animation/powerup/one_more_life.canim") );
      set_stock(1);
      break;
    case increase_max_energy:
      if ( get_player_index() == 2 )
        set_animation( get_level_globals().get_animation
                       ("animation/powerup/increase_max_energy-alt.canim") );
      else
        set_animation( get_level_globals().get_animation
                       ("animation/powerup/increase_max_energy.canim") );
      set_stock(20);
      break;
    case switch_players:
      set_animation( get_level_globals().get_animation
                     ("animation/powerup/switch_players.canim") );
    default:
      {
        CLAW_FAIL( "Not a valid power." );
      }
    }
} // bonus_box::do_set_type()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration of honeypot.
 */
void ptb::bonus_box::create_honeypot_decoration()
{
  bear::decorative_item* item = new bear::decorative_item;

  bool deco = true;

  switch(get_type())
    {
    case fire_power:
      item->set_animation
        ( get_level_globals().get_animation
          ("animation/powerup/small_fire.canim") );
      break;
    case air_power:
      item->set_animation
        ( get_level_globals().get_animation
          ("animation/powerup/small_air.canim") );
      break;
    case water_power:
      item->set_animation
        ( get_level_globals().get_animation
          ("animation/powerup/small_water.canim") );
      break;
    case stones_stock:
    case stones_big_stock:
      item->set_animation
        (get_level_globals().get_animation
         ("animation/stones/stone.canim" ) );
      break;

    default:
      deco = false;
    }

  if ( deco )
    {
      item->set_z_position(get_z_position()+1);
      item->set_mass(1);
      item->set_density
        (0.8 * get_layer().get_world().get_average_density
         (get_bounding_box()));
      item->set_kill_when_leaving(true);

      new_item( *item );

      item->set_top_middle(get_top_middle());

      CLAW_ASSERT( item->is_valid(),
                   "In bonus_box class: the decoration of honeypot isn't "
                   "correctly initialized" );

      bear::decorative_effect* decoration_effect = new bear::decorative_effect;

      decoration_effect->set_duration(1.5);
      bear::visual::color init_color, end_color;
      init_color.set(1,1,1,0.6);
      end_color.set(1,1,1,0);
      decoration_effect->set_color( init_color, end_color );
      decoration_effect->set_item(item, true);

      new_item(*decoration_effect);
    }
  else
    delete item;
} // bonus_box::create_honeypot_decoration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send a notification when a player steals max energy bonus.
 */
void ptb::bonus_box::send_thief_notification(unsigned int index)
{
  status_layer_notification_message msg;
  
  msg.set_notification( index, bear::visual::sprite(), gettext("Thief"));

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // bonus_box::send_thief_notification()
