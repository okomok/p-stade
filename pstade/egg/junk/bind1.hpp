#ifndef BOOST_PP_IS_ITERATING
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Assume f is a 3ary function:
//   bind1(f, a1)(a2, a3)
//     is equivalent to
//   lambda::bind(f, a1, lambda::_1, lambda::_2)(a2, a3)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/ref.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_params.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./add_const_reference.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base, BOOST_PP_ENUM_PARAMS(PSTADE_n, class Arg)>
    struct PSTADE_PP_CAT3(baby_bind, PSTADE_n, _result)
    {
        Base m_base;
        BOOST_PP_REPEAT(PSTADE_n, PSTADE_arg, ~)

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply { }; // msvc warns if incomplete.

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/baby_bind_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            Base const(
                PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_n, typename add_const_reference<Arg, >::type)
                PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
            )
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_base(
            BOOST_PP_ENUM_PARAMS(n, m_arg),
            BOOST_PP_ENUM_PARAMS(n, a)
        );
    }


#undef n
#endif
