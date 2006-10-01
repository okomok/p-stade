#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/merge_range.hpp>


#include <iostream>
#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/tests.hpp>
#include <pstade/oven/to_stream.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng1("acdfilmmrtvwxz");
        std::string rng2("beghjkmnopqsuy");
        BOOST_CHECK( oven::equals(rng1|merged(rng2), std::string("abcdefghijklmmmnopqrstuvwxyz")) );
        oven::copy(rng1|merged(rng2), oven::to_stream(std::cout));

        //BOOST_CHECK( oven::test_forward(rng1|merged(rng2)) ); nonswappable...
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
