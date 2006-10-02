#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/set_intersection_range.hpp>


#include <iostream>
#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/tests.hpp>
#include <pstade/oven/to_stream.hpp>
#include <pstade/oven/c_str_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng1("13579");
        std::string rng2("1239");
        BOOST_CHECK( oven::equals(rng1|set_intersected(rng2), std::string("139")) );
        oven::copy(rng1|set_intersected(rng2), oven::to_stream(std::cout));
    }
    {
        std::string rng1("13579");
        std::string rng2("112358");
        BOOST_CHECK( oven::equals(rng1|set_intersected(rng2), std::string("135")) );
        oven::copy(rng1|set_intersected(rng2), oven::to_stream(std::cout));
        oven::set_intersection(rng1, rng2, oven::to_stream(std::cout));
    }
    {
        std::string rng1("abbbfh");
        c_str_range<char const> rng2("abbcdffhh");
        BOOST_CHECK( oven::equals(rng1|set_intersected(rng2), std::string("abbfh")) );
        oven::copy(rng1|set_intersected(rng2), oven::to_stream(std::cout));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
