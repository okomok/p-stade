#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/begin_end.hpp>


#include <algorithm>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string rng1("hello, begin_end");
        std::string rng2(rng1);
        BOOST_CHECK( std::equal(rng1|begins, rng1|ends, rng2|begins) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
