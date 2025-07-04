// basic_ios member functions -*- C++ -*-

// Copyright (C) 1999-2020 Free Software Foundation, Inc.
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

/** @file bits/basic_ios.tcc
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{ios}
 */

#ifndef _BASIC_IOS_TCC
#define _BASIC_IOS_TCC 1

#pragma GCC system_header

#include "/home/dreame/gcc-10.5.0-install/include/c++/10.5.0/x86_64-pc-linux-gnu/bits/c++config.h"
#include <bits/basic_ios.h>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::clear(iostate __state)
    {
      if (this->rdbuf())
	_M_streambuf_state = __state;
      else
	  _M_streambuf_state = __state | badbit;
      if (this->exceptions() & this->rdstate())
	__throw_ios_failure(__N("basic_ios::clear"));
    }

  template<typename _CharT, typename _Traits>
    basic_streambuf<_CharT, _Traits>*
    basic_ios<_CharT, _Traits>::rdbuf(basic_streambuf<_CharT, _Traits>* __sb)
    {
      basic_streambuf<_CharT, _Traits>* __old = _M_streambuf;
      _M_streambuf = __sb;
      this->clear();
      return __old;
    }

  template<typename _CharT, typename _Traits>
    basic_ios<_CharT, _Traits>&
    basic_ios<_CharT, _Traits>::copyfmt(const basic_ios& __rhs)
    {
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 292. effects of a.copyfmt (a)
      if (this != &__rhs)
	{
	  // Per 27.1.1, do not call imbue, yet must trash all caches
	  // associated with imbue()

	  // Alloc any new word array first, so if it fails we have "rollback".
	  _Words* __words = (__rhs._M_word_size <= _S_local_word_size) ?
	                     _M_local_word : new _Words[__rhs._M_word_size];

	  // Bump refs before doing callbacks, for safety.
	  _Callback_list* __cb = __rhs._M_callbacks;
	  if (__cb)
	    __cb->_M_add_reference();
	  _M_call_callbacks(erase_event);
	  if (_M_word != _M_local_word)
	    {
	      delete [] _M_word;
	      _M_word = 0;
	    }
	  _M_dispose_callbacks();

	  // NB: Don't want any added during above.
	  _M_callbacks = __cb;
	  for (int __i = 0; __i < __rhs._M_word_size; ++__i)
	    __words[__i] = __rhs._M_word[__i];
	  _M_word = __words;
	  _M_word_size = __rhs._M_word_size;

	  this->flags(__rhs.flags());
	  this->width(__rhs.width());
	  this->precision(__rhs.precision());
	  this->tie(__rhs.tie());
	  this->fill(__rhs.fill());
	  _M_ios_locale = __rhs.getloc();
	  _M_cache_locale(_M_ios_locale);

	  _M_call_callbacks(copyfmt_event);

	  // The next is required to be the last assignment.
	  this->exceptions(__rhs.exceptions());
	}
      return *this;
    }

  // Locales:
  template<typename _CharT, typename _Traits>
    locale
    basic_ios<_CharT, _Traits>::imbue(const locale& __loc)
    {
      locale __old(this->getloc());
      ios_base::imbue(__loc);
      _M_cache_locale(__loc);
      if (this->rdbuf() != 0)
	this->rdbuf()->pubimbue(__loc);
      return __old;
    }

  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::init(basic_streambuf<_CharT, _Traits>* __sb)
    {
      // NB: This may be called more than once on the same object.
      ios_base::_M_init();

      // Cache locale data and specific facets used by iostreams.
      _M_cache_locale(_M_ios_locale);

      // NB: The 27.4.4.1 Postconditions Table specifies requirements
      // after basic_ios::init() has been called. As part of this,
      // fill() must return widen(' ') any time after init() has been
      // called, which needs an imbued ctype facet of char_type to
      // return without throwing an exception. Unfortunately,
      // ctype<char_type> is not necessarily a required facet, so
      // streams with char_type != [char, wchar_t] will not have it by
      // default. Because of this, the correct value for _M_fill is
      // constructed on the first call of fill(). That way,
      // unformatted input and output with non-required basic_ios
      // instantiations is possible even without imbuing the expected
      // ctype<char_type> facet.
      _M_fill = _CharT();
      _M_fill_init = false;

      _M_tie = 0;
      _M_exception = goodbit;
      _M_streambuf = __sb;
      _M_streambuf_state = __sb ? goodbit : badbit;
    }

  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::_M_cache_locale(const locale& __loc)
    {
      if (__builtin_expect(has_facet<__ctype_type>(__loc), true))
	_M_ctype = std::__addressof(use_facet<__ctype_type>(__loc));
      else
	_M_ctype = 0;

      if (__builtin_expect(has_facet<__num_put_type>(__loc), true))
	_M_num_put = std::__addressof(use_facet<__num_put_type>(__loc));
      else
	_M_num_put = 0;

      if (__builtin_expect(has_facet<__num_get_type>(__loc), true))
	_M_num_get = std::__addressof(use_facet<__num_get_type>(__loc));
      else
	_M_num_get = 0;
    }

  // Inhibit implicit instantiations for required instantiations,
  // which are defined via explicit instantiations elsewhere.
#if _GLIBCXX_EXTERN_TEMPLATE
  extern template class basic_ios<char>;

#ifdef _GLIBCXX_USE_WCHAR_T
  extern template class basic_ios<wchar_t>;
#endif
#endif

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std

#endif
