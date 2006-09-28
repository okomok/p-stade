#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/null_terminate_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int sample[] = { 1,2,3,4,5,0,7,8,9 };
        int answer[] = { 1,2,3,4,5 };
        BOOST_CHECK( oven::equals(sample|null_terminated, answer) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
