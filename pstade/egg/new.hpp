#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_NEW_HPP
#define PSTADE_EGG_NEW_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./little_apply.hpp"
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    namespace new_detail {


        template<class X>
        struct little
        {
        // 0ary
            typedef X *nullary_result_type;

            template<class Result>
            Result call() const
            {
                return new X();
            }

        // 1ary-
            template<class Myself, PSTADE_EGG_LITTLE_APPLY_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
            struct apply
            {
                typedef X *type;
            };

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/new.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace new_detail


    template<class X>
    struct X_new_ :
        function<new_detail::little<X>, by_perfect>
    { };


} } // namespace pstade::egg


#define  PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS (pstade::egg::X_new_, (class))
#include PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE()


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return new X(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
