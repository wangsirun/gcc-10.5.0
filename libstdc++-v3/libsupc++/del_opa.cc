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

#if !_GLIBCXX_HOSTED
// A freestanding C runtime may not provide "free" -- but there is no
// other reasonable way to implement "operator delete".
namespace std
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
  extern "C" void free(void*);
_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
#else
# include <cstdlib>
#endif

#include "new"

// The sized deletes are defined in other files.
#pragma GCC diagnostic ignored "-Wsized-deallocation"

_GLIBCXX_WEAK_DEFINITION void
operator delete(void* ptr, std::align_val_t) noexcept
{
#if _GLIBCXX_HAVE_ALIGNED_ALLOC || _GLIBCXX_HAVE_POSIX_MEMALIGN \
    || _GLIBCXX_HAVE_MEMALIGN
  std::free (ptr);
#elif _GLIBCXX_HAVE__ALIGNED_MALLOC
  _aligned_free (ptr);
#else
  if (ptr)
    std::free (((void **) ptr)[-1]); // See aligned_alloc in new_opa.cc
#endif
}
