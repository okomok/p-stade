#ifndef BOOST_EGG_PREPROCESSOR_BITS_ENUM_BINARY_PARAMS_HPP
#define BOOST_EGG_PREPROCESSOR_BITS_ENUM_BINARY_PARAMS_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/egg/preprocessor/bits_enum.hpp>


// (0)(1)(1) -> A0 B0, A1 const B1, A2 const B2
#define BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, A, B) \
    BOOST_EGG_PP_BITS_ENUM_R(R, Bits, BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_w0, BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_w1, (2, (A, B))) \
/**/

    #define BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_w0(R, I, A_B) \
        BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(0, A_B), I) BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(1, A_B), I) \
    /**/

    #define BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_w1(R, I, A_B) \
        BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(0, A_B), I) const BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(1, A_B), I) \
    /**/


#endif
