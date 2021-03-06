#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_OF_APPLY_LITTLE_HPP
#define PSTADE_EGG_DETAIL_OF_APPLY_LITTLE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/affect.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./apply_little.hpp"
#include "./bytag_at.hpp"
#include "./little_of.hpp"
#include "./strategy_of.hpp"
#include "./unref.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class FunCall>
    struct of_apply_little;

#define PSTADE_unref(Z, I, _) typename unref<typename bytag_at<stg_t, n, I>::type, BOOST_PP_CAT(A, I)>::type
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/of_apply_little.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_unref


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct of_apply_little<Fun(BOOST_PP_ENUM_PARAMS(n, A))>
    {
        typedef typename
            affect_cv<Fun, typename little_of<Fun>::type>::type
        little_t;

        typedef typename
            affect_cv<Fun, typename strategy_of<Fun>::type>::type
        stg_t;

        typedef typename
            apply_little<little_t, BOOST_PP_ENUM(n, PSTADE_unref, ~)>::type
        type;
    };


#undef  n
#endif
