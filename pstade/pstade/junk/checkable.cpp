#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/checkable.hpp>


using namespace pstade;


void test()
{
    {
        checkable<int> i;
        BOOST_CHECK(!i);
        i = 10;
        BOOST_CHECK(i);
        BOOST_CHECK(*i == 10);
        checkable<int> j = i;
        BOOST_CHECK(*i == *j);
        BOOST_CHECK(i == j);
    }
    {
        checkable<int> i;
        BOOST_CHECK(!i);
        i.reset(10);
        BOOST_CHECK(i);
        BOOST_CHECK(*i == 10);
    }
    {
        checkable<int> i(10);
        BOOST_CHECK(i);
        i.reset();
        BOOST_CHECK(!i);
    }
    {
        checkable<int> i = 10;
        BOOST_CHECK(i);
        i = 10;
        BOOST_CHECK(i);
        BOOST_CHECK(*i == 10);
        checkable<int> j(11);
        BOOST_CHECK(*i < *j);
        BOOST_CHECK(i < j);
    }
    {
        checkable<int> i(10);
        checkable<int> j = i;
        BOOST_CHECK(i == j);
    }
    {
        checkable<int> i(10);
        checkable<int> j;
        j = i;
        BOOST_CHECK(i == j);
    }
#if 0
    {
        checkable<int> i;
        checkable<int> j = i;
        BOOST_CHECK(!i);
        BOOST_CHECK(!j);
    }
    {
        checkable<int> i;
        checkable<int> j;
        j = i;
        BOOST_CHECK(!i);
        BOOST_CHECK(!j);
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
