#ifndef PSTADE_IF_DEBUG_HPP
#define PSTADE_IF_DEBUG_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question: Could have been the following?
//
// BOOST_PP_IF(PSTADE_IS_DEBUG, BOOST_PP_IDENTITY(...), BOOST_PP_EMPTY)()
//
// #if !defined(NDEBUG)
//     #define PSTADE_IS_DEBUG() 1
// #else
//     #define PSTADE_IS_DEBUG() 0
// #endif


#if !defined(NDEBUG) || defined(PSTADE_IF_DEBUG_DEBUG)

    #define PSTADE_IF_DEBUG(X) \
        X \
    /**/

#else

    #define PSTADE_IF_DEBUG(X) \
    /**/

#endif


#endif
