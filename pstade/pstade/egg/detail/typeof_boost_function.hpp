#ifndef PSTADE_EGG_DETAIL_TYPEOF_BOOST_FUNCTION_HPP
#define PSTADE_EGG_DETAIL_TYPEOF_BOOST_FUNCTION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/function.hpp> // no way of forward declaration
#include <boost/typeof/std/memory.hpp> // allocator
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()


BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function, (class)(class))


#endif
