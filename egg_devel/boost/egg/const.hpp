#ifndef BOOST_EGG_CONST_HPP
#define BOOST_EGG_CONST_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/pod_assert.hpp>
#include <boost/egg/detail/unparen.hpp>
#include <boost/egg/detail/unused.hpp>


#define BOOST_EGG_CONST(F, O) \
    BOOST_EGG_POD_ASSERT_OF(F, O); \
    BOOST_EGG_UNPAREN(F) const BOOST_EGG_UNUSED(O) \
/**/


#include <boost/egg/detail/suffix.hpp>
#endif
