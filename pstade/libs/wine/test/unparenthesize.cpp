#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unparenthesize.hpp>


#include <map>
#include <utility>
#include <boost/foreach.hpp>


// Workaround:
// I don't know what happens...
#if !defined(BOOST_MSVC)
#define PSTADE_WINE_TEST_TYPENAME typename
#else
#define PSTADE_WINE_TEST_TYPENAME
#endif


template< class T >
void test_dependent()
{
    BOOST_FOREACH (
        typename PSTADE_UNPARENTHESIZE((std::pair<int, T>)) p,
        PSTADE_WINE_TEST_TYPENAME PSTADE_UNPARENTHESIZE((std::map<int, T>))()
    ) {
        (void)p;
        BOOST_CHECK(false);
    }
}


void test()
{
    using namespace pstade;

    BOOST_FOREACH (
        PSTADE_UNPARENTHESIZE((std::pair<int, int>)) p,
        PSTADE_UNPARENTHESIZE((std::map<int, int>))()
    ) {
        (void)p;
        BOOST_CHECK(false);
    }

    ::test_dependent<int>();
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
