#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_APPLY_LITTLE_HPP
#define BOOST_EGG_DETAIL_APPLY_LITTLE_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/pstade/preprocessor.hpp>
#include "../config.hpp" // BOOST_EGG_MAX_LINEAR_ARITY
#include "./apply_little_n.hpp"
#include "./array_resurrect.hpp"


namespace pstade { namespace egg {


    template<class Little, PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(BOOST_EGG_MAX_LINEAR_ARITY), class A, = void)>
    struct apply_little;

    // 1ary-
#define PSTADE_array_resurrect(Z, N, A) BOOST_EGG_ARRAY_RESURRECT(BOOST_PP_CAT(A, N))
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/apply_little.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_array_resurrect


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Little, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply_little<Little, BOOST_PP_ENUM_PARAMS(n, A)> :
        BOOST_PP_CAT(apply_little, n)<
            Little,
            BOOST_PP_ENUM(n, PSTADE_array_resurrect, A)
        >
    { };


#undef n
#endif
