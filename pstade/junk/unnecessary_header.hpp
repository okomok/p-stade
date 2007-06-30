#ifndef PSTADE_UNNESESSARY_HEADER_HPP
#define PSTADE_UNNESESSARY_HEADER_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Usage:
//
//     #include <necessary0.hpp>
//     #include <necessary1.hpp>
//     #define  PSTADE_UNNESESSARY_PARAMS (XXX_HPP, <xxx.hpp>)
//     #include PSTADE_UNNESESSARY()


#include <boost/preprocessor/tuple/elem.hpp>


#define PSTADE_guard  BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_UNNESESSARY_PARAMS)
#define PSTADE_header BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_UNNESESSARY_PARAMS)


#if !defined(PSTADE_guard)
    #define PSTADE_guard
    #include PSTADE_header
    #undef PSTADE_guard
#endif


#undef  PSTADE_header
#undef  PSTADE_guard

#undef  PSTADE_UNNESESSARY_PARAMS


#endif
