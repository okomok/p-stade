#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_PACK_HPP
#define PSTADE_OVEN_PACK_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/egg/baby_apply.hpp>
#include <pstade/egg/config.hpp> // PSTADE_EGG_MAX_ARITY
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace pack_detail {


    struct baby
    {
        template< class Myself, PSTADE_EGG_BABY_APPLY_PARAMS(PSTADE_EGG_MAX_ARITY, Range) >
        struct PSTADE_EGG_BABY_APPLY;

        // 1ary-
    #define PSTADE_iter_rng(Z, N, _) make_iter_range(BOOST_PP_CAT(rng, N))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/oven/pack.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_iter_rng
    };


} // namespace pack_detail


typedef egg::function<pack_detail::baby> T_pack;
PSTADE_POD_CONSTANT((T_pack), pack) = {{}};


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


    template< class Myself, BOOST_PP_ENUM_PARAMS(n, class Range) >
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, Range)>
    {
        typedef
            boost::tuples::tuple<
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename iter_range_of<Range, >::type)
            >
        type;
    };

    template< class Result, BOOST_PP_ENUM_PARAMS(n, class Range) >
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, Range, & rng)) const
    {
        return Result(
            BOOST_PP_ENUM(n, PSTADE_iter_rng, ~)
        );
    }


#undef n
#endif
