#ifndef BOOST_EGG_DETAIL_EAT_MUTABLE_HPP
#define BOOST_EGG_DETAIL_EAT_MUTABLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>


#define BOOST_EGG_EAT_MUTABLE(Cv) \
    BOOST_PP_CAT(BOOST_EGG_EAT_MUTABLE_, Cv) \
/**/

    #define BOOST_EGG_EAT_MUTABLE_mutable
    #define BOOST_EGG_EAT_MUTABLE_const const
    #define BOOST_EGG_EAT_MUTABLE_volatile volatile


#endif
