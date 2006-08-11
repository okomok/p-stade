#ifndef PSTADE_FORCE_INLINE_HPP
#define PSTADE_FORCE_INLINE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://article.gmane.org/gmane.comp.lib.boost.user/20228


#include <boost/config.hpp>


#if defined(__GNUC__)
     #define PSTADE_FORCE_INLINE __attribute__((always_inline))
     #define PSTADE_NO_INLINE    __attribute__((noinline))
#elif defined(BOOST__MSVC)
     #define PSTADE_FORCE_INLINE __forceinline
     #define PSTADE_NO_INLINE    __declspec(noinline)
#else
     #define PSTADE_FORCE_INLINE inline
     #define PSTADE_NO_INLINE
#endif


#endif
