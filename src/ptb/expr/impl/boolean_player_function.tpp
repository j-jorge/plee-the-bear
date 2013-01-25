/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::boolean_player_function class.
 * \author Julien Jorge.
 */
#include "ptb/util/player_util.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param player_index The index of the player on which we call the method.
 * \param g The level_globals of the level in which the player is searched.
 */
template<typename FunctionType>
ptb::boolean_player_function<FunctionType>::boolean_player_function
( unsigned int player_index, const bear::engine::level_globals* g )
  : m_player_index(player_index), m_player(NULL), m_level_globals(g)
{
  search_player();
} // boolean_player_function::boolean_player_function()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param m The function to call with the instance of the player as the only
 *        parameter.
 * \param player_index The index of the player on which we call the method.
 * \param g The level_globals of the level in which the player is searched.
 */
template<typename FunctionType>
ptb::boolean_player_function<FunctionType>::boolean_player_function
( FunctionType m, unsigned int player_index,
  const bear::engine::level_globals* g )
  : m_player_index(player_index), m_function(m), m_level_globals(g)
{
  search_player();
} // boolean_player_function::boolean_player_function()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a copy of this expression.
 */
template<typename FunctionType>
bear::expr::base_boolean_expression*
ptb::boolean_player_function<FunctionType>::clone() const
{
  return new boolean_player_function<FunctionType>(*this);
} // boolean_player_function::clone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Evaluate the expression.
 */
template<typename FunctionType>
bool ptb::boolean_player_function<FunctionType>::evaluate() const
{
  search_player();

  if ( m_player != NULL )
    return m_function(m_player);
  else
    {
      claw::logger << claw::log_error
                   << "boolean_player_function evaluated without players, the"
                   << " result is 'false'." << std::endl;
      return false;
    }
} // boolean_player_function::evaluate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the fonction to call.
 * \param m The function to call.
 */
template<typename FunctionType>
void ptb::boolean_player_function<FunctionType>::set_function
( FunctionType m )
{
  m_function(m);
} // boolean_player_function::set_function()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the index of the player on which the function is called.
 * \param i The index of the player.
 */
template<typename FunctionType>
void ptb::boolean_player_function<FunctionType>::set_player_index
( unsigned int i )
{
  m_player_index = i;

  // force searching the player at the next evaluation.
  m_player = player_proxy();

} // boolean_player_function::set_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the level_globals of the level in which the player is searched.
 * \param g The level globals.
 */
template<typename FunctionType>
void ptb::boolean_player_function<FunctionType>::set_level_globals
( const bear::engine::level_globals* g )
{
  m_level_globals = g;
} // boolean_player_function::set_level_globals()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search for the player.
 */
template<typename FunctionType>
void ptb::boolean_player_function<FunctionType>::search_player() const
{
  if ( (m_player == NULL) && (m_level_globals != NULL) )
    m_player = util::find_player(*m_level_globals, m_player_index);
} // boolean_player_function::search_player()




/*----------------------------------------------------------------------------*/
/**
 * \brief Construct a boolean_player_function.
 * \param m The function to call.
 * \param player_index The index of the player on which the function is called.
 * \param g The global informations in the level.
 *
 * This function is an easier way to create a boolean function than using the
 * constructor. Compare those two solutions, both creating a boolean function
 * that calls boolean function:
 *
 * \code
 * typedef bool (*some_function)() function_type;
 * boolean_expression f
 *   ( boolean_player_function<function_type>( &my_function, p, g ) );
 * \endcode
 * and
 * \code
 * boolean_expression f( boolean_player_function_maker( &my_function, p, g ) );
 * \endcode
 */
template<typename FunctionType>
ptb::boolean_player_function<FunctionType>
ptb::boolean_player_function_maker
( FunctionType m, unsigned int player_index,
  const bear::engine::level_globals& g )
{
  return boolean_player_function<FunctionType>(m, player_index, &g);
} // boolean_player_function_maker()
