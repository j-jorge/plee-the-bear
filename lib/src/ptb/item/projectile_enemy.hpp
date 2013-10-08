/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a projectile enemy.
 * The valid fields for this item are
   *  - \a projectile_model: (string) \b the model of the projectile,
   *  - any field supported by the parent classes.
   *
 * \author Sébastien Angibaud
 */
#ifndef __PTB_PROJECTILE_ENEMY_HPP__
#define __PTB_PROJECTILE_ENEMY_HPP__

#include "ptb/item_brick/monster_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a projectile enemy.
   * \author Sébastien Angibaud
   */
  class projectile_enemy:
    public monster_item
      < bear::engine::model< bear::engine::base_item > >
  {
    DECLARE_BASE_ITEM(projectile_enemy);

  public:
    /** \brief The type of the parent class. */
    typedef monster_item
    < bear::engine::model< bear::engine::base_item > > super;

  public:
    projectile_enemy();

    void on_enters_layer();

    bool set_string_field
    ( const std::string& name, const std::string& value );
    void set_projectile_model(const std::string& value);
    bool is_valid() const;

    void progress( bear::universe::time_type elapsed_time );
    void leaves_active_region();

  protected:
    virtual void has_attacked(const monster& other);

  private:
    /** \brief The model of the projectile. */
    std::string m_projectile_model;

    /** \brief Indicates if the sting is dead. */
    bool m_is_dead;
  }; // class projectile_enemy
} // namespace ptb

#endif // __PTB_PROJECTILE_ENEMY_HPP__
