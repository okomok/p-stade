#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_SUPPLY_N_HPP
#define PSTADE_EGG_DETAIL_SUPPLY_N_HPP


// PStade.Egg
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
#include <pstade/affect.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/template_arguments.hpp>
#include "./is_placeholder_expression.hpp"


namespace pstade { namespace egg { namespace detail {


    template<
        class Expr,
        PSTADE_PP_ENUM_PARAMS_WITH(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, class A, = void)
    >
    struct supply_placeholder
    {
        typedef typename
            boost::remove_cv<Expr>::type // MPL requires this.
        expr_t;

        typedef typename
            template_arguments_of<expr_t>::type
        target_t;

        // Abundant voids are passed so that `deduce` with `Default` can work. 
        typedef typename
            boost::mpl::BOOST_PP_CAT(apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<
                target_t,
                BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, A)
            >::type
        applied_t;

        typedef typename
            template_arguments_copy<applied_t, expr_t>::type
        supplyd_t;

        typedef typename
            affect_cv<Expr, supplyd_t>::type
        type;
    };


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <pstade/egg/detail/supply_n.hpp>))
    #include BOOST_PP_ITERATE()


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Expr BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct PSTADE_PP_CAT3(supply, n, _meta) :
        boost::mpl::BOOST_PP_CAT(apply, n)<
            typename boost::remove_cv<Expr>::type
            BOOST_PP_ENUM_TRAILING_PARAMS(n, A)
        >
    { };


    template<class Expr BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct BOOST_PP_CAT(supply, n) :
        boost::mpl::eval_if< is_placeholder_expression<Expr>,
            supply_placeholder<Expr BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>,
            PSTADE_PP_CAT3(supply, n, _meta)<Expr BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>
        >
    { };


#undef  n
#endif
