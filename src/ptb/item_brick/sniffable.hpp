/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Base class for objects that can be sniffed.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_SNIFFABLE_HPP__
#define __PTB_SNIFFABLE_HPP__

#include <string>

namespace ptb
{
  /**
   * \brief Base class for objects that can be sniffed.
   *
   * \author Sebastien Angibaud
   */
  class sniffable
  {
  public:
    sniffable(const std::string& category);

    void set_category( const std::string& category );
    std::string get_category() const;

  protected:
    void on_found(unsigned int index);

  private:
    void send_notification(unsigned int index);

  private:
    /** \brief The category of the object. */
    std::string m_category;

  }; // class sniffable
} // namespace ptb

#endif // __PTB_SNIFFABLE_HPP__
