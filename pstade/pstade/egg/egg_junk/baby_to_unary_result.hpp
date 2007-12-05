#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_TO_UNARY_RESULT_HPP
#define PSTADE_EGG_DETAIL_BABY_TO_UNARY_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./add_const_reference.hpp"


namespace pstade { namespace egg { namespace detail {


#define PSTADE_arg(Z, N, _) BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(m_arg, N);
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/baby_to_unary_result.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_arg


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
    struct PSTADE_PP_CAT3(baby_to_unary, n, _result)
    {
        Base m_base;
        BOOST_PP_REPEAT(n, PSTADE_arg, ~)

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

        template<class Myself, class ArgZ>
        struct apply :
            result_of<
                Base const(PSTADE_PP_ENUM_PARAMS_WITH(n, typename add_const_reference<Arg, >::type), ArgZ&)
            >
        { };

        template<class Result, class ArgZ>
        Result call(ArgZ& argZ) const
        {
            return m_base(BOOST_PP_ENUM_PARAMS(n, m_arg), argZ);
        }
    };


#undef n
#endif
