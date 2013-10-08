/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::air_stone class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/stone/air_stone.hpp"

#include "ptb/item/air_bubble.hpp"
#include "ptb/util/player_util.hpp"

#include "generic_items/decorative_item.hpp"
#include "universe/forced_movement/forced_stay_around.hpp"

const bear::universe::time_type ptb::air_stone::s_fall_time = 1;

BASE_ITEM_IMPLEMENT( air_stone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param can_explose Indicates if the player can explose the stone.
 */
ptb::air_stone::air_stone( bool can_explose )
  : m_blast(false), m_reference_item(NULL), m_deflate_time(0),
  m_can_explose(can_explose)
{
  m_offensive_coefficients[air_attack] = 1;
} // air_stone::air_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::air_stone::~air_stone( )
{
  if ( m_reference_item != NULL )
    m_reference_item->kill();
} // air_stone::~air_stone()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::air_stone::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor(get_level_globals().get_model("model/stones/air_stone.cm"));
  start_model_action("attack");
  initialize_intensity();

  if ( m_can_explose )
    {
      m_player = util::find_player( get_level_globals(), get_monster_index() );

      if ( m_player != NULL )
        m_player.add_air_stone(this);
    }
} // air_stone::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::air_stone::progress( bear::universe::time_type elapsed_time )
{
  air_progress(elapsed_time);
} // air_stone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform that a new stone is create.
 */
void ptb::air_stone::inform_new_stone()
{
  start_model_action("explode");
} // air_stone::inform_new_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the air power.
 */
bool ptb::air_stone::has_air_power() const
{
  return true;
} // air_stone::has_air_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::air_stone::inform_no_energy(const monster& attacker)
{
  start_model_action("blast");
} // air_stone::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Kill the item.
 * \pre m_owner != NULL
 */
void ptb::air_stone::kill()
{
  if ( !m_blast )
    start_model_action("blast");
  else if ( m_player != NULL )
    {
      m_player.remove_air_stone(this);

      super::kill();
    }
  else
    super::kill();
} // air_stone::kill()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::air_stone::air_progress( bear::universe::time_type elapsed_time )
{
  rotate();

  if ( !m_blast )
    {
      if ( get_current_action_name() == "attack" )
        {
          if ( get_speed().y < 0 )
            {
              start_model_action("deflate");
              if ( !has_forced_movement() )
                create_movement();
            }
        }
      else if ( get_current_action_name() == "deflate" )
        {
          m_deflate_time += elapsed_time;

          if ( m_deflate_time >= s_fall_time )
            {
              start_model_action("fall");
              set_friction(0.9);
              if ( has_forced_movement() )
                clear_forced_movement();
            }
        }
    }

  default_progress( elapsed_time );

  if ( has_contact() && !m_blast )
    start_model_action("blast");
} // air_stone::air_progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create decorations when the stone blasts.
 */
void ptb::air_stone::create_decorations()
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
  create_decorative_blast("animation/stones/air_sliver_1.canim", speeds[a]);
  create_decorative_blast
    ("animation/stones/air_sliver_2.canim", speeds[(a+1)%5]);
  create_decorative_blast
    ("animation/stones/air_sliver_3.canim", speeds[(a+2)%5]);
  create_decorative_blast
    ("animation/stones/air_sliver_4.canim", speeds[(a+3)%5]);
  create_decorative_blast
    ("animation/stones/air_sliver_5.canim", speeds[(a+4)%5]);
} // air_stone::create_decorations


/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of the intensity.
 */
void ptb::air_stone::initialize_intensity()
{
  double m = (double)rand()/(double)RAND_MAX;
  double h = (double)(rand() / 4)/(double)RAND_MAX + 0.75;
  double v1 = (double)rand()/(double)RAND_MAX;
  double v2 = (double)rand()/(double)RAND_MAX;

  if ( m <= 1.0/3 )
    get_rendering_attributes().set_intensity( h, v1, v2 );
  else if ( m <= 2.0/3 )
    get_rendering_attributes().set_intensity( v1, h, v2 );
  else
    get_rendering_attributes().set_intensity( v1, v2, h );
} // air_stone::initialize_intensity()

/*----------------------------------------------------------------------------*/
/**
 * \brief Blast the stone.
 */
void ptb::air_stone::blast()
{
  if ( !m_blast )
    {
      clear_forced_movement();

      m_blast = true;
      set_speed(bear::universe::speed_type(0, 0));
      set_acceleration(bear::universe::force_type(0, 0));
      set_mass(std::numeric_limits<double>::infinity());
      set_phantom(true);

      create_decorations();

      if ( m_player != NULL )
        m_player.remove_air_stone(this);
    }

  // back to the default intensity for the air blast animation
  get_rendering_attributes().set_intensity( 1.0, 1.0, 1.0 );
} // air_stone::blast()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create decoration when the stone blasts.
 */
void ptb::air_stone::create_decorative_blast
(const std::string& anim_name, const bear::universe::speed_type& speed)
{
  bear::decorative_item* item = new bear::decorative_item;

  item->set_animation
    ( get_level_globals().get_animation(anim_name) );
  item->get_rendering_attributes().combine(this->get_rendering_attributes());
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
  item->set_center_of_mass(get_center_of_mass());

  new_item( *item );

  CLAW_ASSERT( item->is_valid(),
         "The decoration of air_stone isn't correctly initialized" );
} // air_stone::create_decorative_blast()


/*----------------------------------------------------------------------------*/
/**
 * \brief Create movement.
 */
void ptb::air_stone::create_movement()
{
  m_reference_item = new bear::reference_item;
  m_reference_item->set_center_of_mass(get_center_of_mass());
  new_item( *m_reference_item );
  CLAW_ASSERT( m_reference_item->is_valid(),
               "The reference of feather of woodpecker isn't correctly "
               "initialized" );

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
} // air_stone::create_movement()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decorative bubble.
 */
void ptb::air_stone::create_bubble()
{
  if ( is_only_in_environment(bear::universe::water_environment) )
    {
      air_bubble* new_bubble;

      new_bubble= new air_bubble();
      bear::universe::position_type pos = get_center_of_mass();

      new_bubble->set_center_of_mass(pos);
      new_bubble->set_oxygen(0);
      new_bubble->set_z_position(get_z_position() + 1);
      new_item( *new_bubble );
    }
} // air_stone::create_bubble()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::air_stone::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::air_stone, blast, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::air_stone, create_bubble, void );
} // air_stone::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::air_stone )
