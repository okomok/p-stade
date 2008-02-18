#ifndef BOOST_EGG_CONSTRUCT_VARIADIC1_HPP
#define BOOST_EGG_CONSTRUCT_VARIADIC1_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/construct_xxx.hpp>
#include <boost/egg/variadic.hpp>


#define  BOOST_EGG_CONSTRUCT_VARIADIC1_RETURN(T, x, Args) \
    T x = BOOST_EGG_VARIADIC_L { Args } BOOST_EGG_VARIADIC_R; \
    return x; \
/**/
#define  BOOST_EGG_CONSTRUCT_XXX_PARAMS (construct_variadic1, BOOST_EGG_CONSTRUCT_VARIADIC1_RETURN)
#include BOOST_EGG_CONSTRUCT_XXX() 


#include <boost/egg/detail/suffix.hpp>
#endif
