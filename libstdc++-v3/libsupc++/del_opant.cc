// Boilerplate support routines for -*- C++ -*- dynamic memory management.

// Copyright (C) 1997-2020 Free Software Foundation, Inc.
//
// This file is part of GCC.
//
// GCC is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// GCC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include "/home/dreame/gcc-10.5.0-install/include/c++/10.5.0/x86_64-pc-linux-gnu/bits/c++config.h"
#include "new"

_GLIBCXX_WEAK_DEFINITION void
operator delete (void *ptr, std::align_val_t al, const std::nothrow_t&) noexcept
{
  ::operator delete (ptr, al);
}
