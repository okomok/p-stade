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
#include <sstream>
#include <pstade/oven/functions.hpp>
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
    }
    {
        oven::sub_range<std::string> rng1(src);
        oven::sub_range<std::string> rng2 = src;
        oven::sub_range<std::string> rng3(rng1);
        oven::sub_range<std::string> rng4 = rng3;
        BOOST_CHECK( rng1 == rng4 );
        BOOST_CHECK( !(rng1 != rng4 ) );
        rng2 = src;
        BOOST_CHECK( rng1 == rng2 );
        BOOST_CHECK( !(rng1 != rng2 ) );
    }
    {
        std::string src("abc");
        std::stringstream ss;
        oven::sub_range<std::string> rng(src);
        ss << rng;
        BOOST_CHECK( ss.str() == "{a,b,c,}" );
    }
    {
        oven::sub_range<std::string> const rng1(src);
        oven::sub_range<std::string> rng2(rng1);
        oven::sub_range<std::string> rng3 = rng1;
        rng3 = rng1;
        BOOST_CHECK( oven::equals(rng1, rng2) );
        BOOST_CHECK( oven::equals(rng1, rng3) );
    }
#if 0 // rejected
    {
        oven::sub_range<std::string> rng = src|filtered(pstade::is_alnum);
        BOOST_CHECK( oven::equals(rng, src) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
