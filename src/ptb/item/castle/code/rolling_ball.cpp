/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::rolling_ball class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/rolling_ball.hpp"

BASE_ITEM_EXPORT( rolling_ball, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::rolling_ball::rolling_ball()
  : m_on_ground(false)
{
  //set_free_system(true);
  set_system_angle_as_visual_angle(true);
} // rolling_ball::rolling_ball()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::rolling_ball::on_enters_layer()
{
  super::on_enters_layer();

  m_last_visual_position = this->get_center_of_mass();
}// rolling_ball::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rolling_ball::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( has_bottom_contact() )
    {
      if ( !m_on_ground )
	m_on_ground = true;
      
      bear::universe::coordinate_type dist
	( get_center_of_mass().distance(m_last_visual_position) );
      
      if ( get_speed().x < 0 )
	get_rendering_attributes().set_angle
	  ( get_rendering_attributes().get_angle() + dist * 3.14 /
	    ( this->get_height() + this->get_width() ) );
      else
	get_rendering_attributes().set_angle
	  ( get_rendering_attributes().get_angle() - dist * 3.14 /
	    ( this->get_height() + this->get_width() ) );
       
      add_external_force(bear::universe::force_type(750000, 0));
    }
  else
    {
      if ( get_speed().x < 0 )
        add_internal_force(bear::universe::force_type(-200000, 0));
      else
        add_internal_force(bear::universe::force_type(200000, 0));
      m_on_ground = false;
    }

  m_last_visual_position = this->get_center_of_mass();
} // rolling_ball::progress()
