#ifndef BOOST_EGG_PREPROCESSOR_BITS_ENUM_DEDUCED_HPP
#define BOOST_EGG_PREPROCESSOR_BITS_ENUM_DEDUCED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/egg/detail/deduced_const.hpp>
#include <boost/egg/preprocessor/bits_enum.hpp>


// (0)(1)(1) -> A0, A1 const, A2 const
#define BOOST_EGG_PP_BITS_ENUM_DEDUCED_R(R, Bits, A) \
    BOOST_EGG_PP_BITS_ENUM_R(R, Bits, BOOST_EGG_PP_BITS_ENUM_DEDUCED_w0, BOOST_EGG_PP_BITS_ENUM_DEDUCED_w1, A) \
/**/

    #define BOOST_EGG_PP_BITS_ENUM_DEDUCED_w0(R, I, A) BOOST_PP_CAT(A, I)
    #define BOOST_EGG_PP_BITS_ENUM_DEDUCED_w1(R, I, A) BOOST_EGG_DEDUCED_CONST(BOOST_PP_CAT(A, I))


#endif
