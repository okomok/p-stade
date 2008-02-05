#ifndef PSTADE_EGG_DETAIL_GET_POINTER_PREAMBLE_HPP
#define PSTADE_EGG_DETAIL_GET_POINTER_PREAMBLE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/get_pointer.hpp>
#include <pstade/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #define PSTADE_EGG_GET_POINTER_PREAMBLE() using namespace boost;
#else
    #define PSTADE_EGG_GET_POINTER_PREAMBLE() using boost::get_pointer;
#endif


#endif
