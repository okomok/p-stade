#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_APPLY_LITTLE_HPP
#define PSTADE_EGG_DETAIL_APPLY_LITTLE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// This indirection is needed to work around msvc ETI bug.
// You can't use `result` template directly in function declaration.


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/preprocessor.hpp> // PSTADE_PP_ENUM_PARAMS_WITH
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./nullary_result_of_little.hpp"


namespace pstade { namespace egg {


    template<class Little, PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(PSTADE_EGG_MAX_LINEAR_ARITY), class A, = void)>
    struct apply_little;


// 0ary
    template<class Little>
    struct apply_little<Little> :
        detail::nullary_result_of_little<
            typename boost::remove_const<Little>::type
        >
    { };

    template<class Little>
    struct apply_little<Little volatile>;

// 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/apply_little.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Little, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply_little<Little, BOOST_PP_ENUM_PARAMS(n, A)> :
        Little::template apply<Little, BOOST_PP_ENUM_PARAMS(n, A)>
    { };


#undef  n
#endif
