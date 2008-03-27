#ifndef BOOST_EGG_DETAIL_BOOST_FUNCTION_TYPEOF_HPP
#define BOOST_EGG_DETAIL_BOOST_FUNCTION_TYPEOF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/typeof/std/memory.hpp> // allocator
#include <boost/typeof/typeof.hpp>
#include <boost/egg/detail/boost_function_fwd.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()


BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function, (class)(class))


#endif
