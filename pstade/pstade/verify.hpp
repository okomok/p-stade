#ifndef PSTADE_VERIFY_HPP
#define PSTADE_VERIFY_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// for destructor that must never throw


#include <boost/assert.hpp>


#if !defined(NDEBUG) || defined(PSTADE_VERIFY_DEBUG)

    #define PSTADE_VERIFY(Expr) \
        if (!Expr) BOOST_ASSERT(Expr); \
    /**/

#else

    #define PSTADE_VERIFY(Expr) \
        (Expr) \
    /**/

#endif


#endif
