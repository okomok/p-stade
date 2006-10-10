#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/repeat_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/reverse_range.hpp>
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
            rng|repeated(4)|repeated(2),
            expected
        ) );
    }

    {
        std::string ans("xyzxyzxyz");
        std::string src("xyz");
        repeat_range<std::string> vrng1(src, 3);
        BOOST_CHECK( oven::equals(vrng1.source(), src) );

        repeat_range<std::string> vrng2 = vrng1;
        BOOST_CHECK( oven::equals(vrng1, ans) );
        BOOST_CHECK( oven::equals(vrng2, ans) );

        vrng2 = oven::make_repeat_range(src, std::size_t(3));
        BOOST_CHECK( oven::equals(vrng2, ans) );
    }

    {
        BOOST_CHECK( oven::equals(
            std::string("xyz")|repeated(3),
            std::string("xyzxyzxyz")
        ) );

        BOOST_CHECK( oven::equals(
            std::string("xyz")|repeated(2)|repeated(3),
            std::string("xyz")|repeated(3)|repeated(2)
        ) );

        BOOST_CHECK( oven::equals(
            std::string("xyz")|repeated(2)|repeated(3)|repeated(5),
            std::string("xyz")|repeated(3)|repeated(10)
        ) );

        BOOST_CHECK( 3*30 ==
            oven::distance(std::string("xyz")|repeated(2)|repeated(3)|repeated(5))
        );
    }

    {
/*
        BOOST_CHECK( oven::equals(
            std::string("abcd")|repeated(4)|reversed,
            std::string("dcbadcbadcbadcba")
        ) );
*/
        std::string src("abcd");
        BOOST_FOREACH (char ch, src|repeated(5)|reversed) {
            std::cout << ch << std::endl;;
        }

        BOOST_CHECK( oven::equals(
            std::string("xyz")|repeated(2)|repeated(3)|reversed,
            std::string("xyz")|repeated(3)|repeated(2)|reversed
        ) );
    }

    {
        std::string src("abcdefg");
        BOOST_CHECK( (src|repeated(5)).begin()[8] == 'b' );
        BOOST_CHECK( (src|repeated(5)|reversed).begin()[8] == 'f' );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
