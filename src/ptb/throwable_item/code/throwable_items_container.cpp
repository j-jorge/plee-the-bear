/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::throwable_items_container class.
 * \author Sebastien Angibaud
 */
#include "ptb/throwable_item/throwable_items_container.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor. */
ptb::throwable_items_container::throwable_items_container()
  : m_current_throwable_item(0)
{

} // throwable_items_container::throwable_items_container()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::throwable_items_container::~throwable_items_container()
{
  for ( std::size_t i=0; i!=m_throwable_items.size(); ++i )
    delete m_throwable_items[i];
} // throwable_items_container::~throwable_items_container()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the object.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::throwable_items_container::progress
( bear::universe::time_type elapsed_time )
{
  if ( !m_throwable_items.empty() )
    {
      unsigned int new_stock
        (m_throwable_items[m_current_throwable_item]->get_stock());
      bool stock_signal(  m_last_stock != new_stock);

      std::string new_animation
        ( m_throwable_items[m_current_throwable_item]->get_animation());
      bool animation_signal( m_last_animation != new_animation );

      m_last_stock = new_stock;
      m_last_animation = new_animation;

      if ( animation_signal )
        throwable_item_changed(new_animation);

      if ( stock_signal )
        throwable_item_stock_changed(new_stock);
    }
} // throwable_items_container::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if there exists an throwable_item after the current one.
 */
bool ptb::throwable_items_container::has_next() const
{
  return find_next() != m_current_throwable_item;
} // throwable_items_container::has_next();

/*----------------------------------------------------------------------------*/
/**
 * \brief Select the next throwable_item.
 */
void ptb::throwable_items_container::next()
{
  unsigned int new_item(find_next());

  bool signal( m_current_throwable_item != new_item );

  m_current_throwable_item = new_item;

  if ( signal )
    throwable_item_changed
      (m_throwable_items[m_current_throwable_item]->get_animation());
} // throwable_items_container::next();

/*----------------------------------------------------------------------------*/
/**
 * \brief Control if the current throwable_item can be dropped.
 */
void ptb::throwable_items_container::control_current_throwable_item()
{
  if ( m_throwable_items[m_current_throwable_item]->is_empty() )
    next();
} // throwable_items_container::control_current_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Select a given throwable_item.
 * \param name The name of item to select.
 */
void ptb::throwable_items_container::select(const std::string& name)
{
  for ( std::size_t i=0; i!=m_throwable_items.size(); ++i )
    if ( m_throwable_items[i]->get_name() == name )
      {
        m_current_throwable_item = i;
        return;
      }
} // throwable_items_container::select()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the selected throwable_item.
 */
ptb::throwable_item*
ptb::throwable_items_container::get_current_throwable_item() const
{
  CLAW_PRECOND(m_current_throwable_item < m_throwable_items.size());
  return m_throwable_items[m_current_throwable_item];
} // throwable_items_container::get_current_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add an item in the container.
 * \param t The item to add.
 * \pre !contains(t->get_name());
 */
void ptb::throwable_items_container::add( throwable_item* t )
{
  CLAW_PRECOND( !contains(t->get_name()) );

  m_throwable_items.push_back(t);
} // throwable_items_container::add()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a throwable item given his name.
 * \param name The name of the item to remove.
 */
ptb::throwable_item*
ptb::throwable_items_container::remove( const std::string& name )
{
  std::size_t i = 0;
  bool found = false;

  while ( !found && (i != m_throwable_items.size()) )
    if ( m_throwable_items[i]->get_name() == name )
      found = true;
    else
      ++i;

  throwable_item* result = NULL;

  if ( found )
    {
      result = m_throwable_items[i];
      m_throwable_items.erase( m_throwable_items.begin() + i );

      if ( (m_current_throwable_item == i) && (i!=0) )
        --m_current_throwable_item;
    }

  return result;
} // throwable_items_container::remove()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the container has a throwable item with a given name.
 * \param name The name of the item.
 */
bool ptb::throwable_items_container::contains( const std::string& name ) const
{
  std::vector<throwable_item*>::const_iterator it;

  for ( it=m_throwable_items.begin(); it!=m_throwable_items.end(); ++it )
    if ( (*it)->get_name() == name )
      return true;

  return false;
} // throwable_items_container::contains()

/*----------------------------------------------------------------------------*/
/**
 * \brief Find the next throwable_item after the current one.
 */
std::size_t ptb::throwable_items_container::find_next() const
{
  if ( m_throwable_items.empty() )
    return 0;

  bool result = false;
  std::size_t i( (m_current_throwable_item + 1) % m_throwable_items.size() );

  while ( !result && (i != m_current_throwable_item) )
    if ( m_throwable_items[i]->is_empty() )
      i = (i+1) % m_throwable_items.size();
    else
      result = true;

  return i;
} // throwable_items_container::find_next()
