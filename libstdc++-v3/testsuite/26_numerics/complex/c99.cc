// { dg-do compile { target c++11 } }
// { dg-options "-Wno-pedantic" }

// Copyright (C) 2012-2020 Free Software Foundation, Inc.
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

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// libstdc++/54112
#include "/home/dreame/gcc-10.5.0-install/include/c++/10.5.0/x86_64-pc-linux-gnu/bits/c++config.h"
#if _GLIBCXX_HAVE_COMPLEX_H
# include <complex.h>
#endif

int main()
{
#if _GLIBCXX_HAVE_COMPLEX_H && !defined(__STRICT_ANSI__)
  // This is a GNU extension.
  double _Complex x = .5;
  double _Complex y = cacos (x);
  (void)y;
#endif
}
