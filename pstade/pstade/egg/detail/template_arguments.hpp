#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_TEMPLATE_ARGUMENTS_HPP
#define PSTADE_EGG_DETAIL_TEMPLATE_ARGUMENTS_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/at.hpp>
#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/template_arity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>


namespace pstade { namespace egg { namespace detail {


// GCC needs arity parameter to succeed at specialization.
// Note VC++ would crash with this.
#define PSTADE_arity_param() \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM( \
        class Arity = boost::mpl::int_<boost::mpl::aux::template_arity<X>::value>) \
/**/
#define PSTADE_arity(N) \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(boost::mpl::int_<N>) \
/**/

#define PSTADE_at_c(z, N, _) \
    typename boost::mpl::at_c<ArgumentSeq, N>::type \
/**/


    template<
        class X
        PSTADE_arity_param()
    >
    struct template_arguments_of
    {
        typedef boost::mpl::vector0<> type;
    };


    template<
        class ArgumentSeq,
        class X
        PSTADE_arity_param()
    >
    struct template_arguments_copy
    {
        typedef X type;
    };


    // 1ary-BOOST_MPL_LIMIT_METAFUNCTION_ARITY for MPL PlaceholderExpression
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <pstade/template_arguments.hpp>))
    #include BOOST_PP_ITERATE()


#undef  PSTADE_at_c
#undef  PSTADE_arity
#undef  PSTADE_arity_param


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<
        template<BOOST_PP_ENUM_PARAMS(n, class _)> class X,
        BOOST_PP_ENUM_PARAMS(n, class T)
    >
    struct template_arguments_of< X<BOOST_PP_ENUM_PARAMS(n, T)> PSTADE_arity(n) >
    {
        // must be the numbered form for MPL PlaceholderExpression.
        typedef boost::mpl::BOOST_PP_CAT(vector, n)<BOOST_PP_ENUM_PARAMS(n, T)> type;
    };


    template<
        class ArgumentSeq,
        template<BOOST_PP_ENUM_PARAMS(n, class _)> class X,
        BOOST_PP_ENUM_PARAMS(n, class T)
    >
    struct template_arguments_copy< ArgumentSeq, X<BOOST_PP_ENUM_PARAMS(n, T)> PSTADE_arity(n) >
    {
        typedef X<BOOST_PP_ENUM(n, PSTADE_at_c, ~)> type;
    };


#undef n
#endif
