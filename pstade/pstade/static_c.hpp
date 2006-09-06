#ifndef PSTADE_STATIC_C_HPP
#define PSTADE_STATIC_C_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround:
//
// Strictly speaking, the standard doesn't say
// when the definition of 'value' is needed.


// See:
//
// http://groups.google.com/group/comp.lang.c++.moderated/msg/7619a00d3a9dea7c
// http://article.gmane.org/gmane.comp.lib.boost.devel/79456


namespace pstade {


template< class T, T N >
struct static_c
{
    typedef T value_type;
    static T const value = N;
    typedef static_c type;
    typedef static_c<T, N+1> next;
    typedef static_c<T, N-1> prior;
    operator T() const { return value; }
};


template< class T, T N >
T const
static_c<T, N>::value;


} // namespace pstade


#endif
