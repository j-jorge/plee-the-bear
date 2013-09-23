/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the bear::layer_border class.
 * \author Julien Jorge
 */
#include "ptb/item/layer_border.hpp"

#include "engine/game.hpp"
#include "engine/layer/layer.hpp"

#include "ptb/item/player_killer.hpp"
#include "ptb/item/player_stop_block.hpp"

BASE_ITEM_EXPORT( layer_border, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::layer_border::layer_border()
  : m_block_width(100)
{

} // layer_border::layer_border()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::layer_border::set_real_field( const std::string& name, double value )
{
  bool result = true;

  if ( name == "layer_border.block_width" )
    m_block_width = value;
  else
    result = super::set_real_field(name, value);

  return result;
} // layer_border::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if all required fields are initialized.
 */
bool ptb::layer_border::is_valid() const
{
  return (m_block_width > 0) && super::is_valid();
} // layer_border::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::layer_border::build()
{
  create_margins();

  kill();
} // layer_border::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the margins around the layer.
 */
void ptb::layer_border::create_margins()
{
  const claw::math::coordinate_2d<unsigned int> screen_size
    ( bear::engine::game::get_instance().get_screen_size() );

  create_vertical_margin( screen_size.y, 0, "right" );
  create_vertical_margin
    ( screen_size.y, get_layer().get_size().x - m_block_width, "left" );

  create_top_margin( screen_size );
  create_bottom_margin( screen_size );
} // layer_border::create_margins()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the margins on the top the level.
 * \param screen_size The size of the screen.
 */
void ptb::layer_border::create_top_margin
( const claw::math::coordinate_2d<unsigned int>& screen_size )
{
  const bear::universe::size_type max_x = get_layer().get_size().x;
  const bear::universe::size_type width = screen_size.x;
  const bear::universe::size_type y = get_layer().get_size().y - m_block_width;

  bear::universe::coordinate_type x = 0;

  for ( ; x < max_x - width; x += width )
    new_align_block( x, y, width, m_block_width, "bottom" );

  if ( max_x != x )
    new_align_block( x, y, max_x - x, m_block_width, "bottom" );
} // layer_border::create_top_margin()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the margins on the bottom of the level.
 * \param screen_size The size of the screen.
 */
void ptb::layer_border::create_bottom_margin
( const claw::math::coordinate_2d<unsigned int>& screen_size )
{
  const bear::universe::size_type max_x = get_layer().get_size().x;
  const bear::universe::size_type width = screen_size.x;

  bear::universe::coordinate_type x = 0;

  for ( ; x < max_x - width; x += width )
    new_margin_block( x, 0, width, m_block_width, *(new player_killer) );

  if ( max_x != x )
    new_margin_block( x, 0, max_x - x, m_block_width, *(new player_killer) );
} // layer_border::create_bottom_margin()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create vertical margin in the level.
 * \param h The height of the blocks.
 * \param x The X-coordinate of the blocks.
 * \param solid_side The field name to set.
 */
void ptb::layer_border::create_vertical_margin
( bear::universe::size_type h, bear::universe::coordinate_type x,
  const std::string& solid_side ) const
{
  const bear::universe::size_type max_y =
    get_layer().get_size().y - m_block_width;
  bear::universe::coordinate_type y = m_block_width;

  for ( ; y < max_y - h; y += h )
    new_align_block(x, y, m_block_width, h, solid_side);

  new_align_block(x, y, m_block_width, max_y - y, solid_side);
} // layer_border::create_vertical_margin()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a block that aligns the player.
 * \param x X-coordinate of the block.
 * \param y Y-coordinate of the block.
 * \param width The width of the block.
 * \param height The height of the block.
 * \param solid_side The solid side.
 */
void ptb::layer_border::new_align_block
( bear::universe::size_type x, bear::universe::coordinate_type y,
  bear::universe::size_type width,
  bear::universe::size_type height, const std::string& solid_side ) const
{
  player_stop_block* block = new player_stop_block;
  block->set_bool_field(solid_side, true);
  if ( solid_side == "right" )
    block->set_right_side_activation(true);
  else if ( solid_side == "left" )
    block->set_left_side_activation(true); 
  else if ( solid_side == "bottom" )
    block->set_bottom_side_activation(true);

  new_margin_block( x, y, width, height, *block );
} // layer_border::new_align_block()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a block for the margins.
 * \param x X-coordinate of the block.
 * \param y Y-coordinate of the block.
 * \param width The width of the block.
 * \param height The height of the block.
 * \param block The block to add.
 */
void ptb::layer_border::new_margin_block
( bear::universe::coordinate_type x, bear::universe::coordinate_type y,
  bear::universe::size_type width, bear::universe::size_type height,
  base_item& block ) const
{
  block.set_bottom_left( bear::universe::position_type(x, y) );
  block.set_size( width, height );
  block.set_insert_as_static();

  CLAW_ASSERT( block.is_valid(),
               "layer_border::new_margin_block(): the block is not valid" );

  new_item( block );
} // layer_border::new_margin_block()
