#ifndef PSTADE_EGG_DETAIL_CURRY_RESULT_INITIALIZERS_HPP
#define PSTADE_EGG_DETAIL_CURRY_RESULT_INITIALIZERS_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>


#define PSTADE_EGG_CURRY_AUX(N) \
    BOOST_PP_CAT(PSTADE_EGG_CURRY, N) \
/**/


#define PSTADE_EGG_CURRY2(B) \
    { { {{}}, B() } } BOOST_PP_EMPTY \
/**/

#define PSTADE_EGG_CURRY3(B) \
    { { {{}}, PSTADE_EGG_CURRY2(B)() } } BOOST_PP_EMPTY \
/**/

#define PSTADE_EGG_CURRY4(B) \
    { { {{}}, PSTADE_EGG_CURRY3(B)() } } BOOST_PP_EMPTY \
/**/

#define PSTADE_EGG_CURRY5(B) \
    { { {{}}, PSTADE_EGG_CURRY4(B)() } } BOOST_PP_EMPTY \
/**/

#define PSTADE_EGG_CURRY6(B) \
    { { {{}}, PSTADE_EGG_CURRY5(B)() } } BOOST_PP_EMPTY \
/**/

#define PSTADE_EGG_CURRY7(B) \
    { { {{}}, PSTADE_EGG_CURRY6(B)() } } BOOST_PP_EMPTY \
/**/

#define PSTADE_EGG_CURRY8(B) \
    { { {{}}, PSTADE_EGG_CURRY7(B)() } } BOOST_PP_EMPTY \
/**/

#define PSTADE_EGG_CURRY9(B) \
    { { {{}}, PSTADE_EGG_CURRY8(B)() } } BOOST_PP_EMPTY \
/**/

#define PSTADE_EGG_CURRY10(B) \
    { { {{}}, PSTADE_EGG_CURRY9(B)() } } BOOST_PP_EMPTY \
/**/


#endif
