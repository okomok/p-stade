#ifndef PSTADE_EGG_DETAIL_ARRAY_RESURRECT_HPP
#define PSTADE_EGG_DETAIL_ARRAY_RESURRECT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #include "./vc7_1_array_resurrect.hpp"
    #define PSTADE_EGG_ARRAY_RESURRECT(T) typename pstade::egg::detail_vc7_1::array_resurrect< T >::type
#else
    #define PSTADE_EGG_ARRAY_RESURRECT(T) T
#endif


#endif
