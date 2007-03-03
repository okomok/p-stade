#ifndef PSTADE_AS_MPL_LAMBDA_HPP
#define PSTADE_AS_MPL_LAMBDA_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a VC8 bug that 'mpl::apply' occasionally
// fails in the instantiation process of 'boost::result_of'.
//
// These workarounds are known:
//   1. Force FunctionObject instantiation using inheritance like <boost/numeric/functinal.hpp>.
//   2. Call 'mpl::lambda' in non-deduced context like the following macro.
//   3. Don't use 'mpl::apply' when possible.
//
// If a LambdaExpression doesn't have a dependent nested 'type',
// that is to say, it is not a Metafunction with placeholder,
// 'mpl::lambda' seems *not* to fail.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <pstade/unparenthesize.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1400) // VC8

    #include <boost/mpl/lambda.hpp>

    #define PSTADE_AS_MPL_LAMBDA(Lambda) \
        boost::mpl::lambda< PSTADE_UNPARENTHESIZE(Lambda) >::type \
    /**/

#else

    #define PSTADE_AS_MPL_LAMBDA(Lambda) \
        PSTADE_UNPARENTHESIZE(Lambda) \
    /**/

#endif


#endif
