#ifndef PSTADE_COMMA_PROTECT_HPP
#define PSTADE_COMMA_PROTECT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Usage:
//
// PSTADE_IF_DEBUG( PSTADE_COMMA_PROTECT((map<int, char>)) vec; )
// PSTADE_IF_DEBUG( PSTADE_COMMA_PROTECT_D((map<T, U>)) vec; )


// See:
//
// http://d.hatena.ne.jp/Cryolite/20050326
// http://www.kangaroologic.com/interfaces/libs/interfaces/doc/macros/protect.html


#include <boost/type_traits/function_traits.hpp>


#define PSTADE_COMMA_PROTECT(Type) \
    boost::function_traits<void(Type)>::arg1_type \
/**/


#define PSTADE_COMMA_PROTECT_D(Type) \
    typename boost::function_traits<void(Type)>::arg1_type \
/**/


#endif
