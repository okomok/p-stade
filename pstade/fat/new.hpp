#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FAT_NEW_HPP
#define PSTADE_FAT_NEW_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/egg/apply_params.hpp>
#include <pstade/egg/config.hpp> // PSTADE_EGG_MAX_ARITY
#include <pstade/egg/function.hpp>
#include <pstade/egg/nullary_result_of.hpp>


namespace pstade { namespace fat {


    template<class X>
    struct tp_new_
    {
        struct baby
        {
        // 0ary
            typedef X *nullary_result_type;

            template<class Result>
            Result call() const
            {
                return new X();
            }

        // 1ary-
            template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
            struct apply
            {
                typedef X *type;
            };

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/fat/new.hpp>))
            #include BOOST_PP_ITERATE()
        };

        typedef egg::function<baby> type;
    };


    template<class X>
    struct xp_new_ :
        tp_new_<X>::type
    { };


} } // namespace pstade::fat


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::fat::xp_new_, (class))


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
