#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/debug.hpp>
#include <pstade/minimal_test.hpp>


#include <iostream>


void pstade_minimal_test()
{
    {
        PSTADE_DEBUG_EXPR(std::cout << 1 << 2 << 3);
        PSTADE_DEBUG_EXPR(std::cout) << 1 << 2 << 3;
    }
    {
        PSTADE_DEBUG_BLOCK {
            std::cout << 1 << 2 << 3;
        }
    }

    {
        bool b = false;
        PSTADE_DEBUG_EXPR(b) = true;

#if !defined(NDEBUG)
        BOOST_CHECK(b);
#else
        BOOST_CHECK(!b);
#endif
    }

    {
        bool b = false;
        PSTADE_DEBUG_BLOCK {
            b = true;
        }

#if !defined(NDEBUG)
        BOOST_CHECK(b);
#else
        BOOST_CHECK(!b);
#endif
    }

    {
#if !defined(NDEBUG)
        BOOST_CHECK(is_debug::value);
        BOOST_CHECK(!is_ndebug::value);
#else
        BOOST_CHECK(!is_debug::value);
        BOOST_CHECK(is_ndebug::value);
#endif
    }

    {
#if !defined(NDEBUG)
        debugging();
#else
        bool thrown = false;
        try {
            debugging();
        } catch (...) {
            thrown = true;
        }
        BOOST_CHECK(thrown);
#endif
    }
}
