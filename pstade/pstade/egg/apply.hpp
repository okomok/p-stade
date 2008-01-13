#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_APPLY_HPP
#define PSTADE_EGG_APPLY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "./apply_decl.hpp"
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./forward.hpp"


namespace pstade { namespace egg {


    namespace apply_detail {


        template<class Strategy>
        struct little
        {
            template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
            struct PSTADE_EGG_APPLY_DECL;

        #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_LINEAR_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_max_arity, <pstade/egg/apply.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity
        };


    } // namespace apply_detail


    template<class Strategy = by_perfect>
    struct X_apply :
        function<apply_detail::little<Strategy>, Strategy>
    { };

    typedef X_apply<>::function_type T_apply;
PSTADE_ADL_BARRIER(apply) {
    PSTADE_POD_CONSTANT((T_apply), apply) = {{}};
}


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<F(PSTADE_EGG_FORWARDING_META_ARGS(n, A, Strategy const))>
    { };

    template<class Result, class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(F& f BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return f(PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy const));
    }


#undef n
#endif
