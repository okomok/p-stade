#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_APPLY_HPP
#define PSTADE_EGG_APPLY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "./apply_params.hpp"
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY


namespace pstade { namespace egg {


    namespace apply_detail {


        struct baby
        {
        // 1ary-
            template<class Myself, PSTADE_EGG_APPLY_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
            struct apply { }; // msvc warns if incomplete.

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/apply.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace apply_detail


    typedef function<apply_detail::baby, by_perfect> op_apply;
    PSTADE_ADL_BARRIER(apply) {
        PSTADE_POD_CONSTANT((op_apply), apply) = {{}};
    }


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<A0(BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(n, A, & BOOST_PP_INTERCEPT))>
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return a0(BOOST_PP_ENUM_SHIFTED_PARAMS(n, a));
    }


#undef n
#endif
