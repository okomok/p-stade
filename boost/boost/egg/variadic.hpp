#ifndef BOOST_EGG_VARIADIC_HPP
#define BOOST_EGG_VARIADIC_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_cref.hpp>
#include <boost/egg/poly.hpp>
#include <boost/egg/unfuse.hpp>


namespace boost { namespace egg {


    typedef by_cref by_variadic;


    template<
        class Little,
        class Strategy      = use_default,
        class PackExpr      = use_default,
        class NullaryResult = use_default
    >
    struct variadic :
        result_of_unfuse<
            function<Little, by_variadic>,
            NullaryResult,
            PackExpr,
            Strategy
        >
    { };

    #define BOOST_EGG_VARIADIC_L BOOST_EGG_UNFUSE_L {
    #define BOOST_EGG_VARIADIC_R } BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_VARIADIC(L) BOOST_EGG_VARIADIC_L L BOOST_EGG_VARIADIC_R


    template<
        class Expr,
        class Strategy      = use_default,
        class PackExpr      = use_default,
        class NullaryResult = use_default
    >
    struct variadic_poly :
        result_of_unfuse<
            typename poly<Expr, by_variadic>::type,
            NullaryResult,
            PackExpr,
            Strategy
        >
    { };

    #define BOOST_EGG_VARIADIC_POLY() BOOST_EGG_UNFUSE_L BOOST_EGG_POLY() BOOST_EGG_UNFUSE_R


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
