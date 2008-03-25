#ifndef BOOST_EGG_DETAIL_NS_CONST_REF_HPP
#define BOOST_EGG_DETAIL_NS_CONST_REF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Used with "./ns_result_of.hpp".


#include <boost/egg/detail/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #include <boost/egg/detail/vc7_1_const_ref.hpp>
    #define BOOST_EGG_NS_CONST_REF(A) boost::egg::detail_vc7_1::const_ref< A >
#else
    #define BOOST_EGG_NS_CONST_REF(A) A const &
#endif


#endif
