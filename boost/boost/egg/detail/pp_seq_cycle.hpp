#ifndef BOOST_EGG_DETAIL_PP_SEQ_CYCLE_HPP
#define BOOST_EGG_DETAIL_PP_SEQ_CYCLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/repetition/repeat.hpp>


// Seq -> Seq Seq .. Seq
#define BOOST_EGG_PP_SEQ_CYCLE(Seq, Size) \
    BOOST_PP_REPEAT(Size, BOOST_EGG_PP_SEQ_CYCLE_op, Seq) \
/**/

    #define BOOST_EGG_PP_SEQ_CYCLE_op(Z, N, Seq) \
        Seq \
    /**/


#endif
