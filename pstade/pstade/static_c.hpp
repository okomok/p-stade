#ifndef PSTADE_STATIC_C_HPP
#define PSTADE_STATIC_C_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround for:
//
// Strictly speaking, the standard doesn't say
// when the definition of 'value' is needed.


// See:
//
// http://groups.google.com/group/comp.lang.c++.moderated/msg/7619a00d3a9dea7c
// http://article.gmane.org/gmane.comp.lib.boost.devel/79456


namespace pstade {


template< class T, T v >
struct static_c
{
    static const T value = v;
};


template< class T, T v >
const T
static_c<T, v>::value;


} // namespace pstade


#endif
