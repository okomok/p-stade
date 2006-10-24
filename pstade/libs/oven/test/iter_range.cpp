#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/iter_range.hpp>


#include <string>
#include <sstream>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/filter_range.hpp>
#include <pstade/oven/regularize_range.hpp>
#include <pstade/locale.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("hello,iter_range!!!!");
    {
        oven::iter_range<std::string::iterator> rng(src);
        std::vector<char> expected = src|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng, expected
        ) );
    }
    {
        oven::iter_range<std::string::iterator> rng1(src);
        oven::iter_range<std::string::iterator> rng2 = src;
        oven::iter_range<std::string::iterator> rng3(rng1);
        oven::iter_range<std::string::iterator> rng4 = rng3;
        oven::iter_range<std::string::iterator> rng5;
        BOOST_CHECK( rng1 == rng4 );
        BOOST_CHECK( !(rng1 != rng4 ) );
        rng2 = src;
        BOOST_CHECK( rng1 == rng2 );
        BOOST_CHECK( !(rng1 != rng2 ) );
    }
    {
        std::stringstream ss;
        oven::iter_range<std::string::iterator> rng(src);
        ss << rng;
        std::string str = ss.str();
        BOOST_CHECK( src == str );
    }
#if 0 // rejected
    {
        oven::iter_range<std::string::iterator> rng = src|filtered(pstade::is_alpha)|regularized;
        BOOST_CHECK( oven::equals(rng, src) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
