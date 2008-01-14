#ifndef BOOST_EGG_DETAIL_ARRAY_RESURRECT_HPP
#define BOOST_EGG_DETAIL_ARRAY_RESURRECT_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #include "./vc7_1_array_resurrect.hpp"
    #define BOOST_EGG_ARRAY_RESURRECT(T) typename pstade::egg::detail_vc7_1::array_resurrect< T >::type
#else
    #define BOOST_EGG_ARRAY_RESURRECT(T) T
#endif


#endif
