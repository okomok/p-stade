#ifndef BOOST_EGG_PP_SEQ_RANGE_HPP
#define BOOST_EGG_PP_SEQ_RANGE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/repetition/repeat_from_to.hpp>


// (1, 5) -> (1)(2)(3)(4)
#define BOOST_EGG_PP_SEQ_RANGE(N, M) \
    BOOST_PP_REPEAT_FROM_TO(N, M, BOOST_EGG_PP_SEQ_RANGE_op, ~) \
/**/

    #define BOOST_EGG_PP_SEQ_RANGE_op(Z, N, _) \
        (N) \
    /**/


#endif
