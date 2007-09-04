#ifndef PSTADE_EGG_APPLY_PARAMS_HPP
#define PSTADE_EGG_APPLY_PARAMS_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>


#define PSTADE_EGG_APPLY_PARAMS(N, A) \
    class BOOST_PP_CAT(A, 0) BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(N), PSTADE_EGG_APPLY_PARAMS_op, A) \
/**/

    #define PSTADE_EGG_APPLY_PARAMS_op(Z, N, A) , class BOOST_PP_CAT(A, N) = void


#endif
