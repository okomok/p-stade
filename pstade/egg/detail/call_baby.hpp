#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_CALL_BABY_HPP
#define PSTADE_EGG_DETAIL_CALL_BABY_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "../config.hpp"
#include "./call_baby_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Result>
    struct call_baby<boost::use_default, Result>
    {
    // 0ary
        template<class Baby>
        static Result call(Baby& baby)
        {
            return baby.template call<Result>();
        }

    // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/call_baby.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Baby, BOOST_PP_ENUM_PARAMS(n, class A)>
    static Result call(Baby& baby, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a))
    {
        return baby.template call<Result>(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
