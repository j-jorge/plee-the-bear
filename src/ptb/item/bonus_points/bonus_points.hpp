/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A class describing an item that adds point at the end of the level.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_POINTS_HPP__
#define __PTB_BONUS_POINTS_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/with_expression_assignment.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A class describing an item that adds point at the end of the level.
   *
   * The valid fields for this item are:
   *  - \a name: (string) the name of given points,
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_points:
    public bear::engine::base_item,
    public bear::engine::with_boolean_expression_assignment,
    public bear::engine::with_linear_expression_assignment
  {
    DECLARE_BASE_ITEM(bonus_points);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    bonus_points();
    explicit bonus_points( const std::string& name, unsigned int points = 0 );

    void build();
    bool set_string_field(const std::string& name, const std::string& value);
    bool set_u_integer_field( const std::string& name, unsigned int value );

    const std::string& get_name() const;
    unsigned int get_points() const;
    const std::string& get_bonus_id() const;
    void update_bonus_state() const;

    void set_points( const bear::expr::linear_expression& e );
    void set_condition( const bear::expr::boolean_expression& e );
    bool is_level_bonus() const;
    void set_picture_filename( const std::string& filename );
    const std::string& get_picture_filename() const;
    void set_picture_name( const std::string& name );
    const std::string& get_picture_name() const;

  private:
    void do_set_expression( const bear::expr::boolean_expression& e );
    void do_set_expression( const bear::expr::linear_expression& e );
    void update_bonus() const;
    virtual void on_give_points() const;

  private:
    /* \brief The identifier of the bonus. */
    std::string m_bonus_id;

    /* \brief The name of the bonus. */
    std::string m_bonus_name;

    /* \brief Number of points to give. */
    bear::expr::linear_expression m_bonus_points;

    /* \brief The expression to check. */
    bear::expr::boolean_expression m_condition;

    /* \brief The filename of the bonus picture. */
    std::string m_picture_filename;

    /* \brief The name of the bonus picture in spritepos file. */
    std::string m_picture_name;
  
  }; // class bonus_points
} // namespace ptb

#endif // __PTB_BONUS_POINTS_HPP__
