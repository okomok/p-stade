#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_BIND_LEFT1_HPP
#define BOOST_EGG_DETAIL_BIND_LEFT1_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// bind_left1(f, a1)(a2, a3)
//   is equivalent to f(a1, a2, a3).


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/pstade/pass_by.hpp>
#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/preprocessor.hpp>
#include <boost/egg/pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../by_cref.hpp"
#include "../by_perfect.hpp"
#include "../config.hpp" // BOOST_EGG_MAX_ARITY
#include "./bound_arg.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base, class Arg>
    struct little_bind_left1_result
    {
        Base m_base;
        Arg m_arg;

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

    // 1ary-
        template<class Myself, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

    #define PSTADE_max_arity BOOST_PP_DEC(BOOST_EGG_MAX_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <boost/egg/detail/bind_left1.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    };


    template<class Base, class Arg>
    struct result_of_bind_left1
    {
        typedef
            function<little_bind_left1_result<Base, Arg>, by_perfect>
        type;
    };


    #define BOOST_EGG_BIND_LEFT1_L { {
    #define BOOST_EGG_BIND_LEFT1_M ,
    #define BOOST_EGG_BIND_LEFT1_R } }
    #define BOOST_EGG_BIND_LEFT1(F, A) BOOST_EGG_BIND_LEFT1_L F BOOST_EGG_BIND_LEFT1_M A BOOST_EGG_BIND_LEFT1_R


    struct little_bind_left1
    {
        template<class Myself, class Base, class Arg>
        struct apply :
            result_of_bind_left1<
                typename pass_by_value<Base>::type,
                typename bound_arg<Arg>::type
            >
        { };

        template<class Result, class Base, class Arg>
        Result call(Base& base, Arg& arg) const
        {
            Result r = BOOST_EGG_BIND_LEFT1(base, arg);
            return r;
        }
    };

    typedef function<little_bind_left1, by_cref> T_bind_left1;
    PSTADE_POD_CONSTANT((T_bind_left1), bind_left1) = {{}};


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            Base const(
                typename unbound_arg<Arg>::type,
                PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
            )
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_base(
            m_arg,
            BOOST_PP_ENUM_PARAMS(n, a)
        );
    }


#undef n
#endif
