#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/outdirected.hpp>
#include <pstade/oven/indirected.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include <vector>
#include "./detail/v1_core.hpp"
#include <pstade/egg/is_same.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = { 1,2,3,4,5 };
        int *ans[] = { &rng[0], &rng[1], &rng[2], &rng[3], &rng[4] };
        std::vector<int *> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(rng|outdirected, expected) );
    }


    {
        std::string src("abcde");

        BOOST_CHECK( oven::equals( src|outdirected|indirected, src, pstade::egg::is_same ) );
        BOOST_CHECK( oven::equals( src|outdirected|indirected|outdirected|indirected|outdirected|indirected, src, pstade::egg::is_same ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
