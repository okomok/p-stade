#ifndef PSTADE_UNPARENTHESIZE_HPP
#define PSTADE_UNPARENTHESIZE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20050326
// http://www.kangaroologic.com/interfaces/libs/interfaces/doc/macros/protect.html
// 'BOOST_PARAMETER_PARENTHESIZED_TYPE' with Boost v1.34


// Note:
//
// 'PSTADE_UNPARENTHESIZE((T const))' is not supported.
// Instead, use 'PSTADE_UNPARENTHESIZE((T)) const'.
// If 'T' is a dependent-name, add 'typename'.


namespace pstade {


struct void_
{ };


// If 'T' is a dependent-name,
// you can always add 'typename' to this
// even if 'Decayed' is not dependent.
// See "./concept.hpp".

template< class Decayed, class T = void >
struct unparenthesize;

template< class Decayed, class T >
struct unparenthesize<void(Decayed), T>
{
    typedef Decayed type;
};

template< class T >
struct unparenthesize<void(void_), T>
{
    typedef void type;
};


} // namespace pstade


#define PSTADE_UNPARENTHESIZE(Decayed) \
    pstade::unparenthesize<void(Decayed)>::type \
/**/


#endif
