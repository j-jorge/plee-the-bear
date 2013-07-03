/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::gauge class.
 * \author Sebastien Angibaud
 */
#include "ptb/gauge.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::gauge::gauge()
  : m_value(100), m_max_value(100), m_activated(false)
{
} // gauge::gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::gauge::gauge(double max_value)
  : m_value(max_value), m_max_value(max_value), m_activated(false)
{
} // gauge::gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of the gauge.
 * \param value The new value of the gauge.
 */
void ptb::gauge::set_value(double value)
{
  m_value = value;
  if ( m_value >= m_max_value )
    value = m_max_value;
} // gauge::set_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a value at the value of the gauge.
 * \param value The new value of the gauge.
 */
void ptb::gauge::add_value(double value)
{
  m_value += value;

  if ( m_value >= m_max_value )
    m_value = m_max_value;
} // gauge::set_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a value at the value of the gauge.
 * \param value The new value of the gauge.
 */
void ptb::gauge::remove_value(double value)
{
  if ( m_value >= value )
    m_value -= value;
  else
    m_value = 0;
} // gauge::remove_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activate or desactivate the gauge.
 * \param value The new statut.
 */
void ptb::gauge::set_activated(bool value)
{
  m_activated = value;
} // gauge::set_activated()

/*----------------------------------------------------------------------------*/
/**
 * \brief Fill the gauge.
 */
void ptb::gauge::fill()
{
  m_value = m_max_value;
} // gauge::fill()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the value of the gauge.
 */
double ptb::gauge::get_value() const
{
  return m_value;
} // gauge::get_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the maximum value of the gauge.
 */
double ptb::gauge::get_max_value() const
{
  return m_max_value;
} // gauge::get_max_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the gauge is activated.
 */
bool ptb::gauge::is_activated() const
{
  return m_activated;
} // gauge::is_activated()
