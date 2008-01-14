#ifndef BOOST_EGG_DETAIL_AS_MPL_LAMBDA_HPP
#define BOOST_EGG_DETAIL_AS_MPL_LAMBDA_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a msvc8/9 bug that 'mpl::apply<PlaceholderExpression,..>'
// occasionally fails in the instantiation process of 'boost::result_of'.
//
// These workarounds are known:
//   1. Don't use 'mpl::apply' when possible.
//   2. Hide PlaceholderExpression by using inheritance like <boost/numeric/functional.hpp>.
//      -- this way may require nullary result_of specialization to be reworked, though.
//   3. Call 'mpl::lambda' in non-deduced context like the following macro. 
//
// If a PlaceholderExpression doesn't have a dependent nested 'type',
// in other words, if it is not a Metafunction with placeholder, 'mpl::apply' seems *not* to fail.


#include <boost/egg/pstade/boost_workaround.hpp>
#include <boost/egg/pstade/unparenthesize.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1400) || BOOST_WORKAROUND(BOOST_MSVC, == 1500)

    #include <boost/mpl/lambda.hpp>

    #define BOOST_EGG_AS_MPL_LAMBDA(PlaceholderExpr) \
        boost::mpl::lambda< PSTADE_UNPARENTHESIZE(PlaceholderExpr) >::type \
    /**/

#else

    #define BOOST_EGG_AS_MPL_LAMBDA \
        PSTADE_UNPARENTHESIZE \
    /**/

#endif


#endif
