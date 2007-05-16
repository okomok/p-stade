#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/sub_range.hpp>


#include <string>
#include "./core.hpp"
#include <pstade/oven/filtered.hpp>
#include <pstade/locale.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("hello,sub_range!");
    {
        oven::sub_range<std::string> rng(src);
        std::vector<char> expected = src|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng, expected
        ) );

        BOOST_CHECK( oven::test_is_lightweight_proxy(rng) );
    }
    {
        oven::sub_range<std::string> rng1(src);
        oven::sub_range<std::string> rng2 = src;
        oven::sub_range<std::string> rng3(rng1);
        oven::sub_range<std::string> rng4 = rng3;
        oven::sub_range<std::string> rng5 = make_iter_range(src);
        BOOST_CHECK( rng1 == rng4 );
        BOOST_CHECK( !(rng1 != rng4 ) );
        rng2 = src;
        BOOST_CHECK( rng1 == rng2 );
        BOOST_CHECK( !(rng1 != rng2 ) );
        BOOST_CHECK( rng1 == rng5 );
    }
    {
        oven::sub_range<std::string> const rng1(src);
        oven::sub_range<std::string> rng2(rng1);
        oven::sub_range<std::string> rng3 = rng1;
        rng3 = rng1;
        BOOST_CHECK( oven::equals(rng1, rng2) );
        BOOST_CHECK( oven::equals(rng1, rng3) );
    }
    {
        iter_range<std::string::iterator> irng(src);
        sub_range<std::string> srng = irng; // implicit conversion
        BOOST_CHECK( equals(irng, srng) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
