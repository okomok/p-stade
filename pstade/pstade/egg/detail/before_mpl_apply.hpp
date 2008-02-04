#ifndef PSTADE_EGG_DETAIL_BEFORE_MPL_APPLY_HPP
#define PSTADE_EGG_DETAIL_BEFORE_MPL_APPLY_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a msvc8/9 bug that `mpl::apply<PlaceholderExpression,..>`
// occasionally fails in the instantiation process of `boost::result_of`
//
// These workarounds are known:
//   1. Don't use `mpl::apply` when possible.
//   2. Hide PlaceholderExpression by using inheritance like <boost/numeric/functional.hpp>.
//      -- this way may require nullary result_of specialization to be reworked, though.
//   3. Call `mpl::lambda` outside of result_of instantiation process using the following macro.
//      -- "What is outside" is not well-known, though.


#include <pstade/boost_workaround.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310) && BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
    #include <boost/mpl/lambda.hpp>
    #define PSTADE_EGG_BEFORE_MPL_APPLY(Expr) boost::mpl::lambda< Expr >::type
    #define PSTADE_EGG_BEFORE_MPL_APPLY_TPL typename PSTADE_EGG_BEFORE_MPL_APPLY
#else
    #define PSTADE_EGG_BEFORE_MPL_APPLY(Expr) Expr
    #define PSTADE_EGG_BEFORE_MPL_APPLY_TPL PSTADE_EGG_BEFORE_MPL_APPLY
#endif


#endif
