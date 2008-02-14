#ifndef PSTADE_ONCE_HPP
#define PSTADE_ONCE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: http://svn.boost.org/trac/boost/ticket/1532


#if (defined(_MSC_VER) && _MSC_VER > 1000) || \
    (defined(__GNUC__) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 30) || (__GNUC__ > 4))) || \
    (defined(__ICC) && __ICC > 1000)
#   define PSTADE_ONCE() once    
#else
#   define PSTADE_ONCE() message("")
#endif


#endif
