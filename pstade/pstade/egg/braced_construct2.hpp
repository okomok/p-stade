#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BRACED_CONSTRUCT2_HPP
#define PSTADE_EGG_BRACED_CONSTRUCT2_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "./apply_decl.hpp"
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./forward.hpp"
#include "./register_nullary_result.hpp"


namespace pstade { namespace egg {


    namespace braced_construct2_detail {


        template<class X, class Strategy>
        struct little
        {
            typedef X nullary_result_type;

            template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
            struct apply
            {
                typedef X type;
            };

        // 0ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/braced_construct2.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace braced_construct2_detail


    template<class X, class Strategy = by_perfect>
    struct X_braced_construct2 :
        function<braced_construct2_detail::little<X, Strategy>, Strategy>
    { };


} } // namespace pstade::egg


PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::X_braced_construct2, (class)(class))


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        Result r = { { PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy) } };
        return r;
    }


#undef n
#endif
