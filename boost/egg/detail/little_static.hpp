#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_LITTLE_STATIC_HPP
#define BOOST_EGG_DETAIL_LITTLE_STATIC_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This can't be implemented by fusing
// for the maximum efficency and the simplest braced-initializers.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/forward.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg { namespace details {


    template<class Fun, class Strategy>
    struct little_static
    {
    // 0ary
        typedef typename
            result_of_<Fun()>::type
        nullary_result_type;

        template<class Re>
        Re call() const
        {
            return Fun()();
        }

    // 1ary-
        template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_LINEAR_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/little_static.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of_<Fun(BOOST_EGG_FORWARDING_META_ARGS(n, A, Strategy const))>
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return Fun()(BOOST_EGG_FORWARDING_ARGS(n, a, Strategy const));
    }


#undef  n
#endif
