#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/candy.hpp>


#include <pstade/miniboost/binary_literal.hpp>


void test()
{
    using namespace pstade;

    {
        char ch = BOOST_BINARY_LITERAL(0010);
        candy::add(ch, BOOST_BINARY_LITERAL(0100));
        BOOST_CHECK( ch == BOOST_BINARY_LITERAL(0110) );
    }
    {
        BOOST_CHECK( BOOST_BINARY_LITERAL(0100) ==
            candy::complement(candy::complement(BOOST_BINARY_LITERAL(0100)))
        );
    }
    {
        BOOST_CHECK( 2 == candy::count(BOOST_BINARY_LITERAL(0101)) );
    }
    {
        BOOST_CHECK( candy::empty(BOOST_BINARY_LITERAL(0000)) );
        BOOST_CHECK(!candy::empty(BOOST_BINARY_LITERAL(0100)) );
    }
    {
        char ch = BOOST_BINARY_LITERAL(0010);
        candy::flip(ch);
        candy::flip(ch);
        BOOST_CHECK( ch == BOOST_BINARY_LITERAL(0010) );
    }
    {
        BOOST_CHECK( candy::is_subset_of(
            BOOST_BINARY_LITERAL(0110), BOOST_BINARY_LITERAL(0111)
        ) );
    }
    {
        char ch = BOOST_BINARY_LITERAL(1110);
        candy::mask(ch, BOOST_BINARY_LITERAL(1011));
        BOOST_CHECK( ch == BOOST_BINARY_LITERAL(1010) );
    }
    {
        char ch = BOOST_BINARY_LITERAL(1110);
        candy::remove(ch, BOOST_BINARY_LITERAL(1010));
        BOOST_CHECK( ch == BOOST_BINARY_LITERAL(0100) );
    }
    {
        char ch = BOOST_BINARY_LITERAL(1110);
        candy::reset(ch, BOOST_BINARY_LITERAL(1000));
        BOOST_CHECK( ch == BOOST_BINARY_LITERAL(0110) );
        candy::reset(ch);
        BOOST_CHECK( candy::empty(ch) );
    }
    {
        char ch = BOOST_BINARY_LITERAL(0110);
        candy::set(ch, BOOST_BINARY_LITERAL(1000));
        BOOST_CHECK( ch == BOOST_BINARY_LITERAL(1110) );
    }
    {
        char ch = BOOST_BINARY_LITERAL(0110);
        BOOST_CHECK( candy::test(ch, BOOST_BINARY_LITERAL(0100)) );
        BOOST_CHECK(!candy::test(ch, BOOST_BINARY_LITERAL(1000)) );
    }
    {
        char ch = BOOST_BINARY_LITERAL(0110);
        BOOST_CHECK( candy::test_any(ch, BOOST_BINARY_LITERAL(0101)) );
        BOOST_CHECK(!candy::test_any(ch, BOOST_BINARY_LITERAL(1001)) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
