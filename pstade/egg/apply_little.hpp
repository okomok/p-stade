#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_APPLY_LITTLE_HPP
#define PSTADE_EGG_APPLY_LITTLE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp> // BOOST_RESULT_OF_NUM_ARGS
#include <pstade/preprocessor.hpp>
#include "./detail/apply_little_n.hpp"
#include "./detail/bytag_at.hpp"
#include "./detail/nullary_result.hpp"
#include "./detail/unref.hpp"


namespace pstade { namespace egg {


#if 0 // do you know better name?
    template<class Little, class Strategy>
    struct nullary_result_of :
        detail::nullary_result< Little, function<Little, Strategy> >
    { };
#endif


    template<class Little, PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(BOOST_RESULT_OF_NUM_ARGS), class A, = void)>
    struct apply_little;


    template<class FunCall, class Little, class Strategy>
    struct of_apply_little;


    // 1ary-
#define PSTADE_unref(Z, I, _) typename detail::unref<BOOST_PP_CAT(A, I), typename detail::bytag_at<Strategy, n, I>::type>::type
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_RESULT_OF_NUM_ARGS, <pstade/egg/apply_little.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_unref


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Little, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply_little<Little, BOOST_PP_ENUM_PARAMS(n, A)> :
        BOOST_PP_CAT(apply_little, n)<Little, BOOST_PP_ENUM_PARAMS(n, A)>
    { };


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A), class Little, class Strategy>
    struct of_apply_little<Fun(BOOST_PP_ENUM_PARAMS(n, A)), Little, Strategy> :
        BOOST_PP_CAT(apply_little, n)<Little, BOOST_PP_ENUM(n, PSTADE_unref, ~)>
    { };


#undef n
#endif
