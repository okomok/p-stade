#ifndef BOOST_LIBS_EGG_TEST_CHECK_IS_RESULT_OF_HPP
#define BOOST_LIBS_EGG_TEST_CHECK_IS_RESULT_OF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/unparen.hpp>


#define CHECK_IS_RESULT_OF(Result, FunCall) \
    BOOST_MPL_ASSERT((boost::is_same< \
        BOOST_EGG_UNPAREN(Result), \
        boost::egg::result_of_<FunCall>::type \
    >)); \
/**/


#endif
