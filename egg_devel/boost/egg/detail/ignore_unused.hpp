#ifndef BOOST_EGG_DETAIL_IGNORE_UNUSED_HPP
#define BOOST_EGG_DETAIL_IGNORE_UNUSED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>


#define BOOST_EGG_IGNORE_UNUSED(A) ((void)(A))


#define BOOST_EGG_IGNORE_UNUSED_PARAMS(N, A) \
    BOOST_PP_REPEAT(N, BOOST_EGG_IGNORE_UNUSED_PARAMS_op, A) \
/**/

    #define BOOST_EGG_IGNORE_UNUSED_PARAMS_op(Z, N, A) \
        BOOST_EGG_IGNORE_UNUSED(BOOST_PP_CAT(A, N)); \
    /**/


#endif
