/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Definition of the class describing a gauge.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_GAUGE_HPP__
#define __PTB_GAUGE_HPP__

namespace ptb
{
  class plee;

  /**
   * \brief The class describing a gauge.
   * \author Sebastien Angibaud
   */
  class gauge
  {
  public:
    gauge();
    gauge(double max_value);

    void set_value(double value);
    void set_activated(bool value);
    void add_value(double value);
    void remove_value(double value);

    void fill();

    double get_value() const;
    double get_max_value() const;
    bool is_activated() const;


  private:
    /* \brief The value of the gauge. */
    double m_value;

    /* \brief The maximum value. */
    double m_max_value;

    /* \brief Indicates if the gauges is activated. */
    bool m_activated;
  }; // class gauge
} // namespace ptb

#endif // __PTB_GAUGE_HPP__





