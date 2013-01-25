/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \brief The class storing the information of the configuration file of the
 *        game.
 * \author Julien Jorge
 */
#ifndef __PTB_CONFIG_FILE_HPP__
#define __PTB_CONFIG_FILE_HPP__

#include <string>

namespace ptb
{
  /**
   * \brief The class storing the information of the configuration file of the
   *        game.
   * \author Julien Jorge
   */
  class config_file
  {
  public:
    config_file();

    void apply() const;
    void save() const;

    void set_fullscreen( bool b );
    void set_sound_on( bool b );
    void set_music_on( bool b );
    void set_sound_volume( double v );
    void set_music_volume( double v );
    void set_friendly_fire( bool b );

  private:
    std::string bool_to_str( bool b ) const;
    void str_to_bool( bool& b, const std::string& s ) const;
    void str_to_double( double& d, const std::string& s ) const;

  private:
    /** \brief Tell if we use the fullscreen mode. */
    bool m_fullscreen;

    /** \brief Tell if we turn on the sounds. */
    bool m_sound_on;

    /** \brief Tell if we turn on the music. */
    bool m_music_on;

    /** \brief Volume of the sounds. */
    double m_sound_volume;

    /** \brief Volume of the music. */
    double m_music_volume;

    /** \brief Tell if the players can harm each other. */
    bool m_friendly_fire;

    /** \brief The name of the configuration file. */
    const std::string m_config_name;

  }; // class config_file
} // namespace ptb

#endif // __PTB_CONFIG_FILE_HPP__
