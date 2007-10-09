#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_LAZY_RESULT_HPP
#define PSTADE_EGG_DETAIL_BABY_LAZY_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "../apply_params.hpp"
#include "../by_cref.hpp"
#include "../lambda/bind.hpp"
#include "../lambda/config.hpp"
#include "./bind1.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base>
    struct baby_lazy_result
    {
        typedef Base base_type;

        Base m_base;

        Base base() const
        {
            return m_base;
        }

    // 0ary
        typedef typename
            result_of<T_lambda_bind(Base const&)>::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return boost::lambda::bind(m_base);
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(PSTADE_EGG_LAMBDA_BIND_TARGET_MAX_ARITY, A)>
        struct apply { };

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_LAMBDA_BIND_TARGET_MAX_ARITY, <pstade/egg/detail/baby_lazy_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    // Notice that we can't make this "perfect",
    // which would disable nested bind-expression magics.

    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            T_lambda_bind(Base const&, PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return boost::lambda::bind(m_base, BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
