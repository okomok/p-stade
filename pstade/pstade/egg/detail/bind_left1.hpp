#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BIND_LEFT1_HPP
#define PSTADE_EGG_DETAIL_BIND_LEFT1_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// bind_left1(f, a1)(a2, a3)
//   is equivalent to f(a1, a2, a3).
// Notice curry2 expects it to work as "normal" bind,
// meaning that by_perfect and bound/unbound is needed.
//
// Note that this can't use variadic<> because of msvc error C1054.


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../by_cref.hpp"
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "../construct_braced2.hpp"
#include "../generator.hpp"
#include "./bound.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Func, class Bound>
    struct little_bind_left1_result
    {
        Func m_func;
        Bound m_bound;

        typename unbound<Bound>::type base() const
        {
            return m_bound;
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/egg/detail/bind_left1.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    };


    template<class Func, class Bound>
    struct result_of_bind_left1
    {
        typedef
            function<little_bind_left1_result<Func, Bound>, by_perfect>
        type;
    };

    #define PSTADE_EGG_BIND_LEFT1_L { {
    #define PSTADE_EGG_BIND_LEFT1_M ,
    #define PSTADE_EGG_BIND_LEFT1_R } }
    #define PSTADE_EGG_BIND_LEFT1(F, A) PSTADE_EGG_BIND_LEFT1_L F PSTADE_EGG_BIND_LEFT1_M A PSTADE_EGG_BIND_LEFT1_R


    typedef
        generator<
            result_of_bind_left1< deduce<mpl_1, as_value>, deduce<mpl_2, as_bound> >::type,
            by_cref,
            X_construct_braced2<>
        >::type
    T_bind_left1;

    PSTADE_POD_CONSTANT((T_bind_left1), bind_left1) = PSTADE_EGG_GENERATOR();


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            Func const(
                typename unbound<Bound>::type,
                PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
            )
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_func(
            m_bound,
            BOOST_PP_ENUM_PARAMS(n, a)
        );
    }


#undef  n
#endif
