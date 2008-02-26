#ifndef BOOST_EGG_PREPROCESSOR_BITS_ENUM_HPP
#define BOOST_EGG_PREPROCESSOR_BITS_ENUM_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>


#define BOOST_EGG_PP_BITS_ENUM_R(R, Bits, When0, When1, Data) \
    BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_PP_BITS_ENUM_op, (3, (When0, When1, Data)), Bits) \
/**/

    #define BOOST_EGG_PP_BITS_ENUM_op(R, W0_W1_D, I, Bit) \
        BOOST_PP_COMMA_IF(I) \
            BOOST_PP_IIF( Bit, \
                BOOST_PP_ARRAY_ELEM(1, W0_W1_D), \
                BOOST_PP_ARRAY_ELEM(0, W0_W1_D) \
            )(R, I, BOOST_PP_ARRAY_ELEM(2, W0_W1_D)) \
    /**/


#endif
