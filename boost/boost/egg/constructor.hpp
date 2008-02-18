#ifndef BOOST_EGG_CONSTRUCTOR_HPP
#define BOOST_EGG_CONSTRUCTOR_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct.hpp>
#include <boost/egg/implicit.hpp>


namespace boost { namespace egg {


    typedef implicit<X_construct<>, by_perfect>::type T_constructor;
    BOOST_EGG_CONST((T_constructor), constructor) = BOOST_EGG_IMPLICIT();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
