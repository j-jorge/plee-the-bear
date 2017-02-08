/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Version of Plee the Bear
 * \author Sebastien Angibaud
 */
#ifndef __PTB_VERSION_HPP__
#define __PTB_VERSION_HPP__

#define PTB_TO_STR_BIS(v) # v
#define PTB_TO_STR(v) PTB_TO_STR_BIS(v)

#define PTB_MAJOR_VERSION 0
#define PTB_MINOR_VERSION 7
#define PTB_PATCH_NUMBER 1
#define PTB_VERSION_STRING "Plee the Bear " \
  PTB_TO_STR(PTB_MAJOR_VERSION) "." \
  PTB_TO_STR(PTB_MINOR_VERSION) "." PTB_TO_STR(PTB_PATCH_NUMBER)

#endif // __PTB_VERSION_HPP__
