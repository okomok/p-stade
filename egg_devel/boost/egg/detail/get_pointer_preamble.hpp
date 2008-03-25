#ifndef BOOST_EGG_DETAIL_GET_POINTER_PREAMBLE_HPP
#define BOOST_EGG_DETAIL_GET_POINTER_PREAMBLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/get_pointer.hpp>
#include <boost/egg/detail/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #define BOOST_EGG_GET_POINTER_PREAMBLE() using namespace boost;
#else
    #define BOOST_EGG_GET_POINTER_PREAMBLE() using boost::get_pointer;
#endif


#endif
