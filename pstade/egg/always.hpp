#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_ALWAYS_HPP
#define PSTADE_EGG_ALWAYS_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include "./apply_params.hpp"
#include "./by_cref.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    namespace always_detail {


        template<class X>
        struct baby
        {
            X m_x;

        // 0ary
            typedef X nullary_result_type;

            template<class Result>
            Result call() const
            {
                return m_x;
            }

        // 1ary-
            template<class Myself, PSTADE_EGG_APPLY_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
            struct apply
            {
                typedef X type;
            };

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/always.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace always_detail


    template<class X>
    struct result_of_always
    {
        typedef function<always_detail::baby<X>, by_cref> type;
    };

    #define PSTADE_EGG_ALWAYS_L { {
    #define PSTADE_EGG_ALWAYS_R } }

    typedef
        generator<
            result_of_always< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace_level1
        >::type
    op_always;

    PSTADE_POD_CONSTANT((op_always), always) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)) const
    {
        return m_x;
    }


#undef n
#endif
