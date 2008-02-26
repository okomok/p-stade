#ifndef BOOST_EGG_PREPROCESSOR_FOR_EACH_BITS_HPP
#define BOOST_EGG_PREPROCESSOR_FOR_EACH_BITS_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/seq.hpp> // HEAD, TAIL
#include <boost/egg/preprocessor/seq_repeat.hpp>


#define BOOST_EGG_PP_FOR_EACH_BITS(Count, Macro, Data) \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_EGG_PP_FOR_EACH_BITS_op, (((2, (Macro, Data))))BOOST_EGG_PP_SEQ_REPEAT((0)(1), Count)) \
/**/

    #define BOOST_EGG_PP_FOR_EACH_BITS_op(R, A_Bits) \
        BOOST_EGG_PP_FOR_EACH_BITS_macro(A_Bits) \
            (R, BOOST_PP_SEQ_TAIL(A_Bits), BOOST_EGG_PP_FOR_EACH_BITS_data(A_Bits)) \
    /**/

    #define BOOST_EGG_PP_FOR_EACH_BITS_macro(A_Bits) BOOST_PP_ARRAY_ELEM(0, BOOST_PP_SEQ_HEAD(A_Bits))
    #define BOOST_EGG_PP_FOR_EACH_BITS_data(A_Bits)  BOOST_PP_ARRAY_ELEM(1, BOOST_PP_SEQ_HEAD(A_Bits))


#endif
