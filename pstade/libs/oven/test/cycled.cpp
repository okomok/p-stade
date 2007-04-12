#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/cycled.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/reversed.hpp>
#include <pstade/oven/offset.hpp>
#include <pstade/oven/taken.hpp>
#include <boost/iterator/counting_iterator.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("1234");
        std::string ans("12341234123412341234123412341234");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|cycled(0, 4)|cycled(0, 2),
            expected
        ) );
    }
    {
        std::string rng("12345*");
        std::string ans("345*12345*12345*12");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|cycled(0, 2)|offset(-4, 2),
            expected
        ) );
    }
    {
        std::string rng("12345*");
        std::string ans("12345*12345*12345*12345*12345*123");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            rng|cycled|taken(6*5+3),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("xyz")|cycled(0, 3),
            std::string("xyzxyzxyz")
        ) );

        BOOST_CHECK( oven::equals(
            std::string("xyz")|cycled(0, 2)|cycled(0, 3),
            std::string("xyz")|cycled(0, 3)|cycled(0, 2)
        ) );

        BOOST_CHECK( oven::equals(
            std::string("xyz")|cycled(0, 2)|cycled(0, 3)|cycled(0, 5),
            std::string("xyz")|cycled(0, 3)|cycled(0, 10)
        ) );

        BOOST_CHECK( 3*30 ==
            oven::distance(std::string("xyz")|cycled(0, 2)|cycled(0, 3)|cycled(0, 5))
        );
    }

    {
/*
        BOOST_CHECK( oven::equals(
            std::string("abcd")|cycled(4)|reversed,
            std::string("dcbadcbadcbadcba")
        ) );
*/
        std::string src("abcd");
        BOOST_FOREACH (char ch, src|cycled(0, 5)|reversed) {
            std::cout << ch << std::endl;;
        }

        BOOST_CHECK( oven::equals(
            std::string("xyz")|cycled(0, 2)|cycled(0, 3)|reversed,
            std::string("xyz")|cycled(0, 3)|cycled(0, 2)|reversed
        ) );
    }

    {
        std::string src("abcdefg");
        BOOST_CHECK( (src|cycled(0, 5)).begin()[8] == 'b' );
        BOOST_CHECK( (src|cycled(0, 5)|reversed).begin()[8] == 'f' );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
