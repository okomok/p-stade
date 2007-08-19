#ifndef PSTADE_EGG_DETAIL_CURRY_RESULT_INITIALIZERS_HPP
#define PSTADE_EGG_DETAIL_CURRY_RESULT_INITIALIZERS_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/preprocessor.hpp>


#define PSTADE_EGG_CURRY_RESULT_INITIALIZER_AUX(N) \
    PSTADE_PP_CAT3(PSTADE_EGG_CURRY, N, _RESULT_INITIALIZER) \
/**/


#define PSTADE_EGG_CURRY2_RESULT_INITIALIZER(B) \
    { { {{}}, B() } } \
/**/

#define PSTADE_EGG_CURRY3_RESULT_INITIALIZER(B) \
    { { {{}}, PSTADE_EGG_CURRY2_RESULT_INITIALIZER(B) } } \
/**/

#define PSTADE_EGG_CURRY4_RESULT_INITIALIZER(B) \
    { { {{}}, PSTADE_EGG_CURRY3_RESULT_INITIALIZER(B) } } \
/**/

#define PSTADE_EGG_CURRY5_RESULT_INITIALIZER(B) \
    { { {{}}, PSTADE_EGG_CURRY4_RESULT_INITIALIZER(B) } } \
/**/

#define PSTADE_EGG_CURRY6_RESULT_INITIALIZER(B) \
    { { {{}}, PSTADE_EGG_CURRY5_RESULT_INITIALIZER(B) } } \
/**/

#define PSTADE_EGG_CURRY7_RESULT_INITIALIZER(B) \
    { { {{}}, PSTADE_EGG_CURRY6_RESULT_INITIALIZER(B) } } \
/**/

#define PSTADE_EGG_CURRY8_RESULT_INITIALIZER(B) \
    { { {{}}, PSTADE_EGG_CURRY7_RESULT_INITIALIZER(B) } } \
/**/

#define PSTADE_EGG_CURRY9_RESULT_INITIALIZER(B) \
    { { {{}}, PSTADE_EGG_CURRY8_RESULT_INITIALIZER(B) } } \
/**/

#define PSTADE_EGG_CURRY10_RESULT_INITIALIZER(B) \
    { { {{}}, PSTADE_EGG_CURRY9_RESULT_INITIALIZER(B) } } \
/**/


#endif
