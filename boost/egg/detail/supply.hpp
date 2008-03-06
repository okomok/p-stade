#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_SUPPLY_HPP
#define BOOST_EGG_DETAIL_SUPPLY_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// This is similar to mpl::apply,
// but can work with incomplete PlaceholderExpression.
// Outmost PlaceHolderExpression is not regarded as Metafunction.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/detail/affect.hpp>
#include <boost/egg/detail/is_mpl_placeholder_expr.hpp>
#include <boost/egg/detail/template_arguments.hpp>


namespace boost { namespace egg { namespace details {


    template<
        class Expr,
        BOOST_EGG_PP_ENUM_PARAMS_WITH(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, class A, = void)
    >
    struct supply_placeholder
    {
        typedef typename
            remove_cv<Expr>::type // MPL requires this.
        expr_t;

        typedef typename
            template_arguments_of<expr_t>::type
        target_t;

        // Abundant voids are passed so that `deduce` with `Default` can work. 
        typedef typename
            mpl::BOOST_PP_CAT(apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<
                target_t,
                BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, A)
            >::type
        applied_t;

        typedef typename
            template_arguments_copy<applied_t, expr_t>::type
        supplied_t;

        typedef typename
            affect_cv<Expr, supplied_t>::type
        type;
    };


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/egg/detail/supply.hpp>))
    #include BOOST_PP_ITERATE()


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Expr BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct BOOST_EGG_PP_CAT3(supply, n, _meta) :
        mpl::BOOST_PP_CAT(apply, n)<
            typename remove_cv<Expr>::type
            BOOST_PP_ENUM_TRAILING_PARAMS(n, A)
        >
    { };


    template<class Expr BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct BOOST_PP_CAT(supply, n) :
        mpl::eval_if< is_mpl_placeholder_expr<Expr>,
            supply_placeholder<Expr BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>,
            BOOST_EGG_PP_CAT3(supply, n, _meta)<Expr BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>
        >
    { };


#undef  n
#endif
