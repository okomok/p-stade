#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_NAMED_RESULT_HPP
#define PSTADE_EGG_DETAIL_BABY_NAMED_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/sequence/container/vector/vector10.hpp>
#include <boost/fusion/sequence/container/vector/vector20.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_params.hpp"
#include "../config.hpp"
#include "./named_arg.hpp"


namespace pstade { namespace egg { namespace detail {


// 0ary
    template<class Base>
    struct baby_named0_result
    {
        typedef Base base_type;
        Base m_base;
        Base base() const { return m_base; }

        typedef typename
            result_of<Base const()>::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return m_base();
        }
    };


    template<class Base>
    struct baby_named3_result
    {
        typedef Base base_type;
        Base m_base;
        Base base() const { return m_base; }

        template<class Myself, class A0, class A1, class A2>
        struct apply
        {
            typedef boost::fusion::vector3<A0, A1, A2> nargs_t;

            typedef typename result_of<detail::xp_get_argument<Base, 0>(nargs_t&, boost::tuples::tuple<>)>::type b0_t;
            typedef typename result_of<detail::xp_get_argument<Base, 1>(nargs_t&, boost::tuples::tuple<b0_t>)>::type b1_t;        
            typedef typename result_of<detail::xp_get_argument<Base, 2>(nargs_t&, boost::tuples::tuple<b0_t, b1_t>)>::type b2_t;

            typedef typename result_of<Base const(b0_t, b1_t, b2_t)>::type type;
        };

        template<class Result, class A0, class A1, class A2>
        Result call(A0 a0, A1 a1, A2 a2) const
        {
            typedef apply<void, A0, A1, A2> apply_;

            typename apply_::nargs_t nargs(a0, a1, a2);
            typename apply_::b0_t b0 = detail::xp_get_argument<Base, 0>()(nargs, boost::tuples::tuple<>());
            typename apply_::b1_t b1 = detail::xp_get_argument<Base, 1>()(nargs, boost::tuples::tuple<typename apply_::b0_t>(b0));
            typename apply_::b2_t b2 = detail::xp_get_argument<Base, 2>()(nargs, boost::tuples::tuple<typename apply_::b0_t, typename apply_::b1_t>(b0, b1));

            return m_base(b0, b1, b2);
        }
    };


// 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_LINEAR_MAX_ARITY, <pstade/egg/detail/baby_named_result.hpp>))
    #include BOOST_PP_ITERATE()


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


#if 0
    template<class Base>
    struct PSTADE_PP_CAT3(baby_named, n, _result)
    {
        template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
        {
            typedef 
            result_of<
                op_lambda_bind(Base const&, PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
            >
        { };

        template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
        {
            return boost::lambda::bind(m_base, BOOST_PP_ENUM_PARAMS(n, a));
        }
    };
#endif


#undef n
#endif
