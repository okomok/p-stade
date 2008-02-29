#ifndef BOOST_EGG_PREPROCESSOR_SEQ_FOR_EACH_PRODUCT_HPP
#define BOOST_EGG_PREPROCESSOR_SEQ_FOR_EACH_PRODUCT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright 2006 Cryolite.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/seq.hpp> // HEAD, TAIL


#define BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT(Seq, Macro, Data) \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT_op, (((2, (Macro, Data))))Seq) \
/**/

    #define BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT_op(R, MD_Seq) \
        BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT_macro(MD_Seq) \
            (R, BOOST_PP_SEQ_TAIL(MD_Seq), BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT_data(MD_Seq)) \
    /**/

    #define BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT_macro(MD_Seq) BOOST_PP_ARRAY_ELEM(0, BOOST_PP_SEQ_HEAD(MD_Seq))
    #define BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT_data(MD_Seq)  BOOST_PP_ARRAY_ELEM(1, BOOST_PP_SEQ_HEAD(MD_Seq))


#endif
