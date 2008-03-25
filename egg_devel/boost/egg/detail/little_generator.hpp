#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_LITTLE_GENERATOR_HPP
#define BOOST_EGG_DETAIL_LITTLE_GENERATOR_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/construct.hpp>
#include <boost/egg/detail/supply.hpp>
#include <boost/egg/detail/use_nullary_result.hpp>


namespace boost { namespace egg { namespace details {


    template<class Expr, class Strategy, class Construct, class NullaryResult>
    struct little_generator
    {
        typedef typename
            if_use_default< Construct, X_construct<> >::type
        construct_t;

    // 0ary
        typedef typename
            eval_if_use_nullary_result< NullaryResult,
                supply0<Expr>
            >::type
        nullary_result_type;

        template<class Re>
        Re call() const
        {
            typedef typename mpl::apply2<construct_t, Re, Strategy>::type cons_t;
            return cons_t()();
        }

     // 1ary-
        template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/egg/detail/little_generator.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        BOOST_PP_CAT(supply, n)<Expr, BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        typedef typename mpl::apply2<construct_t, Re, Strategy>::type cons_t;
        return cons_t()(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
