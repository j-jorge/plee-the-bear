/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::air_fire_stone class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/stone/air_fire_stone.hpp"

#include "ptb/util/player_util.hpp"

#include "generic_items/decorative_item.hpp"
#include "universe/forced_movement/forced_stay_around.hpp"

BASE_ITEM_IMPLEMENT( air_fire_stone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::air_fire_stone::air_fire_stone()
  : m_blast(false), m_reference_item(NULL)
{
  m_offensive_coefficients[air_attack] = 1;
} // air_fire_stone::air_fire_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::air_fire_stone::~air_fire_stone( )
{
  if ( m_reference_item != NULL )
    m_reference_item->kill();
} // air_fire_stone::~air_fire_stone()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::air_fire_stone::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor
    ( get_level_globals().get_model("model/stones/air_fire_stone.cm"));
  start_model_action("attack");

  m_player = util::find_player( get_level_globals(), get_monster_index() );

  if ( m_player != NULL )
    m_player.add_air_stone(this);
} // air_fire_stone::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::air_fire_stone::progress( bear::universe::time_type elapsed_time )
{
  rotate();

  default_progress(elapsed_time);

  if ( has_contact() && !m_blast )
    start_model_action("blast");
} // air_fire_stone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform that a new stone is create.
 */
void ptb::air_fire_stone::inform_new_stone()
{
  start_model_action("blast");
} // air_fire_stone::inform_new_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Kill the item.
 * \pre m_owner != NULL
 */
void ptb::air_fire_stone::kill()
{
  if ( !m_blast )
    start_model_action("blast");
  else if ( m_player != NULL )
    {
      m_player.remove_air_stone(this);

      super::kill();
    }
} // air_fire_stone::kill()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::air_fire_stone::inform_no_energy(const monster& attacker)
{
  start_model_action("blast");
} // air_fire_stone::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the air power.
 */
bool ptb::air_fire_stone::has_air_power() const
{
  return true;
} // air_fire_stone::has_air_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Blast the stonee.
 */
void ptb::air_fire_stone::blast()
{
  if ( !m_blast )
    {
      m_blast = true;
      set_speed(bear::universe::speed_type(0, 0));
      set_acceleration(bear::universe::force_type(0, 0));
      set_mass(std::numeric_limits<double>::infinity());
      set_phantom(true);

      create_decorations();

      if ( m_player != NULL )
        m_player.remove_air_stone(this);
    }
} // air_fire_stone::blast()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create decorations when the stone blasts.
 */
void ptb::air_fire_stone::create_decorations()
{
  unsigned int a = (unsigned int)(5.0 * rand() / RAND_MAX);
  int b = (int)(2.0 * rand() / RAND_MAX);
  if ( b == 0 )
    b = -1;

  std::vector<bear::universe::speed_type> speeds(5);

  speeds[0] = bear::universe::speed_type(500*b, 0);
  speeds[1] = bear::universe::speed_type(500*b, 500);
  speeds[2] = bear::universe::speed_type(-500*b, 300);
  speeds[3] = bear::universe::speed_type(-500*b, 700);
  speeds[4] = bear::universe::speed_type(100*b, 1000);
  create_decorative_blast("animation/stones/sliver_1.canim", speeds[a]);
  create_decorative_blast
    ("animation/stones/sliver_2.canim", speeds[(a+1)%5]);
  create_decorative_blast
    ("animation/stones/sliver_3.canim", speeds[(a+2)%5]);
  create_decorative_blast
    ("animation/stones/sliver_4.canim", speeds[(a+3)%5]);
  create_decorative_blast
    ("animation/stones/sliver_5.canim", speeds[(a+4)%5]);
} // air_fire_stone::create_decorations

/*----------------------------------------------------------------------------*/
/**
 * \brief Create decoration when the stone blasts.
 */
void ptb::air_fire_stone::create_decorative_blast
(const std::string& anim_name, const bear::universe::speed_type& speed)
{
  bear::decorative_item* item = new bear::decorative_item;

  item->set_animation
    (get_level_globals().get_animation(anim_name));
  item->get_rendering_attributes().set_angle(get_visual_angle());
  item->set_kill_on_contact(true);
  item->set_z_position(get_z_position() - 1);
  unsigned int gap_x = (unsigned int)( 16.0 * rand() / RAND_MAX);
  unsigned int gap_y = (unsigned int)( 16.0 * rand() / RAND_MAX);
  item->set_gap(-8 + gap_x, -8 + gap_y);
  item->set_speed(speed);
  item->set_mass(10);
  item->set_density(2);
  item->set_artificial(false);
  item->set_phantom(false);

  new_item( *item );

  item->set_center_of_mass(get_center_of_mass());

  CLAW_ASSERT( item->is_valid(),
         "The decoration of air_stone isn't correctly initialized" );
} // air_fire_stone::create_decorative_blast()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create movement.
 */
void ptb::air_fire_stone::create_movement()
{
  m_reference_item = new bear::reference_item;
  m_reference_item->set_center_of_mass(get_center_of_mass());
  new_item( *m_reference_item );
  CLAW_ASSERT
    ( m_reference_item->is_valid(),
      "The reference of feather of woodpecker isn't correctly initialized" );

  bear::universe::forced_stay_around mvt;
  mvt.set_max_angle( 0.2 );
  mvt.set_speed( 300 );
  mvt.set_max_distance
    ( std::numeric_limits<bear::universe::coordinate_type>::infinity() );
  mvt.set_apply_angle( true );
  set_system_angle_as_visual_angle(true);
  mvt.set_reference_point_on_center(*m_reference_item);
  mvt.set_item(*this);

  set_forced_movement( mvt );
} // air_fire_stone::create_movement()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::air_fire_stone::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::air_fire_stone, blast, void );
} // air_fire_stone::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::air_fire_stone )
