/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An expression returning the result of a call of a function on a player
 *        instance.
 * \author Julien Jorge
 */
#ifndef __PTB_BOOLEAN_PLAYER_FUNCTION_HPP__
#define __PTB_BOOLEAN_PLAYER_FUNCTION_HPP__

#include "ptb/player_proxy.hpp"

#include "expr/base_boolean_expression.hpp"

namespace ptb
{
  /**
   * \brief An expression returning the result of a call of a function on a
   *        player instance.
   *
   * The evaluation of this expression is m(*inst), where \a m is the function
   * passed to the constructor, and \a inst the pointer on a pointer.
   *
   * \author Julien Jorge
   */
  template<typename FunctionType>
  class boolean_player_function:
    public bear::expr::base_boolean_expression
  {
  public:
    explicit boolean_player_function
    ( unsigned int player_index = 0,
      const bear::engine::level_globals* g = NULL );
    explicit boolean_player_function
    ( FunctionType m, unsigned int player_index = 0,
      const bear::engine::level_globals* g = NULL );

    base_boolean_expression* clone() const;
    bool evaluate() const;

    void set_function( FunctionType m );
    void set_player_index( unsigned int i );
    void set_level_globals( const bear::engine::level_globals* g );

  private:
    void search_player() const;

  private:
    /** \brief The index of the player on which we work. */
    unsigned int m_player_index;

    /** \brief The instance on which we call the function. */
    mutable player_proxy m_player;

    /** \brief The function to call. */
    FunctionType m_function;

    /** \brief The level_globals of the level in which the player is
        searched. */
    const bear::engine::level_globals* m_level_globals;

  }; // class boolean_player_function

  template<typename FunctionType>
  boolean_player_function<FunctionType>
  boolean_player_function_maker
  ( FunctionType m, unsigned int player_index,
    const bear::engine::level_globals& g );

} // namespace ptb

#include "ptb/expr/impl/boolean_player_function.tpp"

#endif // __PTB_BOOLEAN_PLAYER_FUNCTION_HPP__
