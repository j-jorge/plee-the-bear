/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The colors used in the frames.
 * \author Julien Jorge
 */
#ifndef __PTB_THEME_COLORS_HPP__
#define __PTB_THEME_COLORS_HPP__

/** \brief The color of the selected items in the menus. */
#define PTB_THEME_SELECTION bear::visual::color_type(211, 215, 239, 64)

/** \brief The color of the bright sides of the controls. */
#define PTB_THEME_LIGHT bear::visual::color_type("C00e2599")

/** \brief The color of the shadows of the controls. */
#define PTB_THEME_DARK bear::visual::color_type("C0071147")

/** \brief The color of the faces of the controls. */
#define PTB_THEME_FACE bear::visual::color_type("C00e0f27")

/** \brief A transparent color. */
#define PTB_THEME_TRANSPARENT bear::visual::color_type(0, 0, 0, 0)

#endif // __PTB_THEME_COLORS_HPP__
