#ifndef PSTADE_EGG_VARIADIC_HPP
#define PSTADE_EGG_VARIADIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./by_cref.hpp"
#include "./deferred.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    typedef by_cref by_variadic;


    template<
        class Little,
        class Strategy      = boost::use_default,
        class PackExpr      = boost::use_default,
        class NullaryResult = boost::use_default
    >
    struct variadic :
        result_of_unfuse<
            function<Little, by_variadic>,
            NullaryResult,
            PackExpr,
            Strategy
        >
    { };

    #define PSTADE_EGG_VARIADIC_L PSTADE_EGG_UNFUSE_L {
    #define PSTADE_EGG_VARIADIC_R } PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_VARIADIC(L) PSTADE_EGG_VARIADIC_L L PSTADE_EGG_VARIADIC_R


    template<
        class Expr,
        class Strategy      = boost::use_default,
        class PackExpr      = boost::use_default,
        class NullaryResult = boost::use_default
    >
    struct variadic_d :
        result_of_unfuse<
            typename deferred<Expr, by_variadic>::type,
            NullaryResult,
            PackExpr,
            Strategy
        >
    { };

    #define PSTADE_EGG_VARIADIC_D() PSTADE_EGG_UNFUSE_L PSTADE_EGG_DEFERRED() PSTADE_EGG_UNFUSE_R


} } // namespace pstade::egg


#endif
