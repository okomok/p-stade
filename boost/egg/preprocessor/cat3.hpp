#ifndef BOOST_EGG_PREPROCESSOR_CAT3_HPP
#define BOOST_EGG_PREPROCESSOR_CAT3_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>


#define BOOST_EGG_PP_CAT3(A0, A1, A2) \
    BOOST_PP_CAT(A0, BOOST_PP_CAT(A1, A2)) \
/**/


#endif
