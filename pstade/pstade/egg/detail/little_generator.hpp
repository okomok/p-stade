#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_GENERATOR_HPP
#define PSTADE_EGG_DETAIL_LITTLE_GENERATOR_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/template_arguments.hpp>
#include <pstade/use_default.hpp>
#include "../apply_decl.hpp"
#include "../construct.hpp"
#include "./mpl_placeholders.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Lambda>
    struct is_placeholder_expression :
        boost::mpl::is_lambda_expression<Lambda>
    { };


    // Work around "ETI" of 'boost::mpl::apply'.

    template<class Lambda>
    struct lambda_to_dummy :
        boost::mpl::eval_if< is_placeholder_expression<Lambda>,
            template_arguments_of<Lambda>,
            boost::mpl::identity<Lambda>
        >
    { };

    template<class Dummy, class Lambda>
    struct dummy_to_lambda :
        boost::mpl::eval_if< is_placeholder_expression<Lambda>,
            template_arguments_copy<Dummy, Lambda>,
            boost::mpl::identity<Dummy>
        >
    { };


    template<
        class Lambda,
        PSTADE_PP_ENUM_PARAMS_WITH(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, class A, = void)
    >
    struct generated_object
    {
        typedef typename
            boost::remove_cv<Lambda>::type // MPL needs this.
        lambda_t;

        typedef typename
            boost::mpl::BOOST_PP_CAT(apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<
                typename lambda_to_dummy<lambda_t>::type,
                BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, A)
            >::type
        dummy_t;

        typedef typename
            affect_cv<Lambda, typename dummy_to_lambda<dummy_t, lambda_t>::type>::type
        type;
    };


    // Even if using 'lambda_to_dummy', 'NullaryResult' must be explicitly specified.
    // E.g. 'my< some_metafunction<_1> >' where 'some_metafunction<void>::type' is ill-formed.

    template<class Lambda, class Strategy, class Construct, class NullaryResult>
    struct little_generator
    {
        typedef typename
            if_use_default< Construct, X_construct<> >::type
        construct_t;

    // 0ary
        typedef NullaryResult nullary_result_type;

        template<class Result>
        Result call() const
        {
            typedef typename boost::mpl::apply2<construct_t, Result, Strategy>::type cons_t;
            return cons_t()();
        }

     // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <pstade/egg/detail/little_generator.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        generated_object<
            Lambda, BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        typedef typename boost::mpl::apply2<construct_t, Result, Strategy>::type cons_t;
        return cons_t()(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
