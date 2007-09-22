#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_RESET_HPP
#define PSTADE_EGG_RESET_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// A "resettable" type must be CopyConstructible and DefaultConstructible.


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <pstade/pod_constant.hpp>
#include "./apply_params.hpp"
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./move_assign.hpp"


namespace pstade { namespace egg {


    struct baby_reset
    {
    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
        struct apply
        {
            typedef void type;
        };

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/reset.hpp>))
        #include BOOST_PP_ITERATE()
    };

    typedef function<baby_reset, by_perfect> op_reset;
    PSTADE_POD_CONSTANT((op_reset), reset) = {{}};


    struct op_move_reset
    {
        typedef void result_type;

        template<class X, class A>
        void operator()(X& x, A a) const
        {
            move_assign(X(a), x);
        }
    };

    PSTADE_POD_CONSTANT((op_move_reset), move_reset) = {};


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    void call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        move_assign(A0(BOOST_PP_ENUM_SHIFTED_PARAMS(n, a)), a0);
    }


#undef n
#endif
