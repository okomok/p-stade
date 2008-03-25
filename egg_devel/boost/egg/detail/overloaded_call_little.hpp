#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_OVERLOADED_CALL_LITTLE_HPP
#define BOOST_EGG_DETAIL_OVERLOADED_CALL_LITTLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/detail/overloaded_call_little_fwd.hpp>


namespace boost { namespace egg { namespace details {


    template<class Little, class Re, class Void>
    struct overloaded_call_little
    {
    // 0ary
        static Re call(Little &little)
        {
            return little.template call<Re>();
        }

    // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/overloaded_call_little.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    static Re call(Little &little, BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a))
    {
        return little.template call<Re>(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
