#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_RESULT_OF_BIND_HPP
#define PSTADE_EGG_DETAIL_RESULT_OF_BIND_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <pstade/preprocessor.hpp>
#include "../bind_n.hpp"
#include "../config.hpp"


namespace pstade { namespace egg {


    template<class Base, class NullaryResult, PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_EGG_MAX_LINEAR_ARITY, class Arg, = void)>
    struct result_of_bind;

    // 0ary-
#define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_LINEAR_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_max_arity, <pstade/egg/detail/result_of_bind.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, class NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
    struct result_of_bind<Base, NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)> :
        BOOST_PP_CAT(result_of_bind, n)<Base, NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)>
    { };


#undef n
#endif
