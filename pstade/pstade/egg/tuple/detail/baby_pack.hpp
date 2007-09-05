#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_TUPLE_BABY_PACK_HPP
#define PSTADE_EGG_TUPLE_BABY_PACK_HPP
#include "../../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include "../../apply_params.hpp"
#include "../../by_ref.hpp"
#include "../config.hpp"


namespace pstade { namespace egg { namespace tuple_detail {


    struct baby_pack
    {
    // 0ary
        typedef boost::tuples::tuple<> nullary_result_type;

        template<class Result>
        Result call() const
        {
            return Result();
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(PSTADE_EGG_TUPLE_MAX_ARITY, A)>
        struct apply { }; // msvc warns if incomplete.

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_TUPLE_MAX_ARITY, <pstade/egg/tuple/detail/baby_pack.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::tuple_detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef boost::tuples::tuple<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)> type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return Result(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
