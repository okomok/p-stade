#ifndef BOOST_EGG_PREPROCESSOR_SEQ_PARAMS_HPP
#define BOOST_EGG_PREPROCESSOR_SEQ_PARAMS_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>


// A -> (A0)(A1)..(AN)
#define BOOST_EGG_PP_SEQ_PARAMS(N, A) \
    BOOST_PP_REPEAT(N, BOOST_EGG_PP_SEQ_PARAMS_op, A) \
/**/

    #define BOOST_EGG_PP_SEQ_PARAMS_op(z, N, A) \
        (BOOST_PP_CAT(A, N)) \
    /**/


#endif
