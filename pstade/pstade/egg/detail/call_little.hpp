#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_CALL_LITTLE_HPP
#define PSTADE_EGG_DETAIL_CALL_LITTLE_HPP
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
#include "./call_little_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Little_, class Result, class EnableIf>
    struct call_little
    {
    // 0ary
        template<class Little>
        static Result call(Little& little)
        {
            return little.template call<Result>();
        }

    // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/call_little.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Little, BOOST_PP_ENUM_PARAMS(n, class A)>
    static Result call(Little& little, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a))
    {
        return little.template call<Result>(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
