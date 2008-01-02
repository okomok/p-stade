#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_NOT_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_NOT_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Avoid fusing; it is possible that 'Base' doesn't support result_of.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "../little_apply.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base>
    struct little_not_result
    {
        Base m_base;

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

    // 0ary
        typedef bool nullary_result_type;

        template<class Result>
        Result call() const
        {
            return !m_base();
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_LITTLE_APPLY_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
        struct apply
        {
            typedef bool type;
        };

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/little_not_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return !m_base(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
