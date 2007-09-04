#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BIND1_HPP
#define PSTADE_EGG_DETAIL_BIND1_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// bind1(f, a1)(a2, a3)
//   is equivalent to f(a1, a2, a3).


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_params.hpp"
#include "../by_cref.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "../function.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base, class Arg>
    struct baby_bind1_result
    {
        Base m_base;
        Arg m_arg;

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
        struct apply { }; // msvc warns if incomplete.

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/egg/detail/bind1.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    };


    template<class Base, class Arg>
    struct result_of_bind1
    {
        typedef
            function<
                baby_bind1_result<Base, Arg>
            >
        type;
    };

    #define PSTADE_EGG_DETAIL_BIND1_L { {
    #define PSTADE_EGG_DETAIL_BIND1_M ,
    #define PSTADE_EGG_DETAIL_BIND1_R } }


    struct baby_bind1
    {
        template<class Myself, class Base, class Arg>
        struct apply :
            result_of_bind1<
                typename boost::remove_cv<Base>::type,
                typename boost::remove_cv<Arg>::type
            >
        { };

        template<class Result, class Base, class Arg>
        Result call(Base& base, Arg& arg) const
        {
            Result r = PSTADE_EGG_DETAIL_BIND1_L base PSTADE_EGG_DETAIL_BIND1_M arg PSTADE_EGG_DETAIL_BIND1_R;
            return r;
        }
    };

    typedef function<baby_bind1, by_cref> op_bind1;
    PSTADE_POD_CONSTANT((op_bind1), bind1) = {{}};


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            Base const(
                Arg const&,
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
