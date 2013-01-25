/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This frame is shown to enter the passwords.
 * \author Julien Jorge.
 */
#ifndef __PTB_FRAME_PASSWORD_HPP__
#define __PTB_FRAME_PASSWORD_HPP__

#include "ptb/frame/frame.hpp"
#include "gui/text_input.hpp"

namespace ptb
{
  /**
   * \brief This frame is shown to choose enter the passwords.
   * \author Julien Jorge.
   */
  class frame_password:
    public frame
  {
  public:
    frame_password( windows_layer* in_layer );

  private:
    void validate();

    void create_controls();
    bear::gui::visual_component* create_input();
    bear::gui::visual_component* create_back();

    void execute_command( const std::vector<std::string>& command ) const;

    void command_load_level( const std::vector<std::string>& command ) const;
    void command_unlock( const std::vector<std::string>& command ) const;
    void command_give
    ( const std::vector<std::string>& command, unsigned int index ) const;
    void command_game_variable( const std::vector<std::string>& command ) const;

    template<typename T>
    void command_game_variable( const std::string& var_value ) const;

  private:
    /** \brief The text control receiving the passwords. */
    bear::gui::text_input* m_password;

  }; // class frame_password
} // namespace ptb

#endif // __PTB_FRAME_PASSWORD_HPP__
