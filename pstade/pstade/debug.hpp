#ifndef PSTADE_DEBUG_HPP
#define PSTADE_DEBUG_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>


#if !defined(NDEBUG) || defined(PSTADE_DEBUG_DEBUG)

    #define PSTADE_DEBUG 1
    #define PSTADE_NDEBUG 0

    #define PSTADE_DEBUG_EXPR(X) \
        (X) \
    /**/

    #define PSTADE_DEBUG_BLOCK \
    /**/

    typedef boost::mpl::true_ is_debug;
    typedef boost::mpl::false_ is_ndebug;

    inline void debugging() { }

#else

    #define PSTADE_DEBUG 0
    #define PSTADE_NDEBUG 1

    namespace pstade { namespace debug_detail {
        // Suppress "conditional expression is constant" warning.
        template<bool b> inline bool always() { return b; }
    } }

    #define PSTADE_DEBUG_EXPR(X) \
        if (pstade::debug_detail::always<true>()) ; else (X) \
    /**/

    #define PSTADE_DEBUG_BLOCK \
        if (pstade::debug_detail::always<false>()) \
    /**/

    typedef boost::mpl::false_ is_debug;
    typedef boost::mpl::true_ is_ndebug;

    inline void debugging() { throw "debugging"; }

#endif


#endif
