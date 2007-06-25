#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/io.hpp>


#include <string>
#include <iostream>
#include <sstream>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/locale.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    {
        std::string src("abc");
        std::stringstream ss;
        oven::iter_range<std::string::iterator> rng(src);
        ss << rng;
        BOOST_CHECK( ss.str() == "{a,b,c}" );
    }
    {
        std::stringstream ss;
        ss << make_iter_range(std::string());
        BOOST_CHECK( ss.str() == "{}" );
    }
    {
        std::stringstream ss;
        ss << make_iter_range(std::string("a"));
        BOOST_CHECK( ss.str() == "{a}" );
    }
    {
        std::stringstream ss("{a,b,c}");
        std::string dst("123");
        BOOST_CHECK(ss >> make_iter_range(dst));
        BOOST_CHECK( dst == "abc" );
    }
    {
        std::string src("abc");
        std::stringstream ss;
        oven::iter_range<std::string::iterator> rng(src);
        ss << range_open('<') << range_close('>') << range_delimiter(' ') << rng;
        BOOST_CHECK( ss.str() == "<a b c>" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
