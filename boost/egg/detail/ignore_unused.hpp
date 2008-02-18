#ifndef BOOST_EGG_DETAIL_IGNORE_UNUSED_HPP
#define BOOST_EGG_DETAIL_IGNORE_UNUSED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if defined(__GNUC__)
    #define BOOST_EGG_IGNORE_UNUSED __attribute__ ((__unused__))
#else
    #define BOOST_EGG_IGNORE_UNUSED
#endif


#endif
