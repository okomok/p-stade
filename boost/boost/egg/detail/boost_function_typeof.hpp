#ifndef BOOST_EGG_DETAIL_BOOST_FUNCTION_TYPEOF_HPP
#define BOOST_EGG_DETAIL_BOOST_FUNCTION_TYPEOF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/typeof/typeof.hpp>
#include <boost/egg/detail/boost_function_fwd.hpp>
#if defined(BOOST_FUNCTION_DEFAULT_ALLOCATOR)
    #include <boost/typeof/std/memory.hpp> // allocator
#endif

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()


#if defined(BOOST_FUNCTION_DEFAULT_ALLOCATOR)
    BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function, (class)(class))
#else
    BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function, (class))
#endif


#endif
