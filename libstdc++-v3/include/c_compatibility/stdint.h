// -*- C++ -*- compatibility header.

// Copyright (C) 2007-2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdint.h
 *  This is a Standard C++ Library header.
 */

#ifndef _GLIBCXX_STDINT_H
#define _GLIBCXX_STDINT_H 1

#pragma GCC system_header

#include "/home/dreame/gcc-10.5.0-install/include/c++/10.5.0/x86_64-pc-linux-gnu/bits/c++config.h"

#if __cplusplus >= 201103L

// For 8.22.1/1 (see C99, Notes 219, 220, 222)
# if _GLIBCXX_HAVE_STDINT_H
#  ifndef __STDC_LIMIT_MACROS
#   define _UNDEF__STDC_LIMIT_MACROS
#   define __STDC_LIMIT_MACROS
#  endif
#  ifndef __STDC_CONSTANT_MACROS
#   define _UNDEF__STDC_CONSTANT_MACROS
#   define __STDC_CONSTANT_MACROS
#  endif
#  include_next <stdint.h>
#  ifdef _UNDEF__STDC_LIMIT_MACROS
#   undef __STDC_LIMIT_MACROS
#   undef _UNDEF__STDC_LIMIT_MACROS
#  endif
#  ifdef _UNDEF__STDC_CONSTANT_MACROS
#   undef __STDC_CONSTANT_MACROS
#   undef _UNDEF__STDC_CONSTANT_MACROS
#  endif
# endif

#ifdef _GLIBCXX_USE_C99_STDINT_TR1

namespace std
{
  using ::int8_t;
  using ::int16_t;
  using ::int32_t;
  using ::int64_t;

  using ::int_fast8_t;
  using ::int_fast16_t;
  using ::int_fast32_t;
  using ::int_fast64_t;

  using ::int_least8_t;
  using ::int_least16_t;
  using ::int_least32_t;
  using ::int_least64_t;

  using ::intmax_t;
  using ::intptr_t;
  
  using ::uint8_t;
  using ::uint16_t;
  using ::uint32_t;
  using ::uint64_t;

  using ::uint_fast8_t;
  using ::uint_fast16_t;
  using ::uint_fast32_t;
  using ::uint_fast64_t;

  using ::uint_least8_t;
  using ::uint_least16_t;
  using ::uint_least32_t;
  using ::uint_least64_t;

  using ::uintmax_t;
  using ::uintptr_t;
} // namespace

#endif // _GLIBCXX_USE_C99_STDINT_TR1

#else

# if _GLIBCXX_HAVE_STDINT_H
#  include_next <stdint.h>
# endif

#endif // C++11

#endif // _GLIBCXX_STDINT_H
