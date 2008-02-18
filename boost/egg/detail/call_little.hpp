#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_CALL_LITTLE_HPP
#define BOOST_EGG_DETAIL_CALL_LITTLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/const.hpp>
#include <boost/egg/detail/apply_little.hpp>
#include <boost/egg/detail/call_little_impl.hpp>


namespace boost { namespace egg {


    struct T_call_little
    {
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/call_little.hpp>))
        #include BOOST_PP_ITERATE()
    };

    BOOST_EGG_CONST((T_call_little), call_little) = {};


} } // namespace boost::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Little BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    typename apply_little<Little BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>::type
    operator()(Little &little BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, &a)) const
    {
        return details::call_little_impl<Little,
            typename apply_little<Little BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>::type
        >::call(little BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef  n
#endif
