#ifndef PSTADE_COMMA_PROTECT_HPP
#define PSTADE_COMMA_PROTECT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20050326
// http://www.kangaroologic.com/interfaces/libs/interfaces/doc/macros/protect.html


// See: <boost/sequence/detail/comma_protect.hpp>
//
// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


namespace pstade {


template< class T >
struct comma_protect;


template< class R, class T >
struct comma_protect<R(T)>
{
    typedef T type;
};


template< class T >
struct comma_protect_eval;


template< class R, class T >
struct comma_protect_eval<R(T)>
{
    typedef typename T::type type;
};


} // namespace pstade


#endif
