#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_APPLY_LITTLE_N_HPP
#define PSTADE_EGG_DETAIL_APPLY_LITTLE_N_HPP
#include "./prefix.hpp"


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


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp> // BOOST_RESULT_OF_NUM_ARGS


namespace pstade { namespace egg {


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_RESULT_OF_NUM_ARGS, <pstade/egg/detail/apply_little_n.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Little, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(apply_little, n) :
        Little::template apply<
            Little const,
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };


#undef n
#endif
