/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::friend_block class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/friend_block.hpp"
#include "universe/derived_item_handle.hpp"

BASE_ITEM_EXPORT( friend_block, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::friend_block::friend_block()
  : m_friend_ghost(NULL)
{
} // friend_block::friend_block()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::friend_block::~friend_block()
{
} // friend_block::~friend_block()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_as_train().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
*/
void ptb::friend_block::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  bool default_col(true);

  if ( m_friend_ghost.get() != NULL )
    {
      if ( m_friend_ghost->possess() )
        {
          player_proxy p(&that);

          if ( p != NULL )
            if ( p == m_friend_ghost->get_player() )
              default_col = false;
        }
    }

  if ( default_col )
    default_collision(info);
}// friend_block::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c base_item.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::friend_block::set_item_field
( const std::string& name, base_item* value )
{
  bool result(true);

  if ( name == "friend_block.friend_ghost" )
    {
      ptb::friend_ghost* g = dynamic_cast<friend_ghost*>(value);
      if ( g != NULL )
        m_friend_ghost = g;
    }
  else
    result = super::set_item_field(name, value);

  return result;
} // friend_block::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::friend_block::is_valid() const
{
  if ( m_friend_ghost.get() == NULL )
    {
      claw::logger << claw::log_error
                   << "friend_block: friend ghost is not initialized."
                   << std::endl;
      return false;
    }
  else
    return super::is_valid();
} // friend_block::is_valid()


