#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/to_counter.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/to_utf8_encoder.hpp>
#include <pstade/oven/adaptor_to_base.hpp>
#include <pstade/unused.hpp>


using namespace pstade;
using namespace oven;


void test()
{
    {
        int const rng[] = { 0,0,1,1,2,3,3,3,4,4,4,4,4,5,5 };
        int i = oven::unique_copy(rng, oven::to_counter(0))|to_base;
        BOOST_CHECK( i == 6 );
        BOOST_CHECK( 7 == oven::counter_base(oven::unique_copy(rng, oven::to_counter(1))) );
    }
    {
        std::wstring rng(L"aabbbcccdddeffg");
        int i = oven::unique_copy(rng, oven::to_utf8_encoder(oven::to_counter(0)))|to_base|to_counter_base;
        BOOST_CHECK( i == 7 );
    }

    {
        std::wstring rng(L"aabbbcccdddeffg");
        int i = oven::unique_copy(rng, oven::to_utf8_encoder(oven::to_counter(0)))|to_base; // still work.
        BOOST_CHECK( i == 7 );
    }
#if 0
    {
        std::wstring rng(L"aabbbcccdddeffg");
        int i = oven::unique_copy(rng, oven::to_utf8_encoder(oven::to_counter(0)))|to_counter_base; // doesn't work, of course.
        BOOST_CHECK( i == 7 );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
