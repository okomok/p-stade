#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/uniqued.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/reverse_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;


    {
        int rng[] = {1,3,3,2,2,1};
        int ans[] = {1,3,2,1};
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|uniqued,
            expected
        ) );
    }

    int src[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
    int ans2[] = { 2, 4, 6, 8, 10, 20, 40, 80, 120 };
    {

        BOOST_CHECK((
            oven::equals( oven::make_uniqued(src), ans2)
        ));
    }


    {
        BOOST_CHECK((
            oven::equals( src|uniqued|reversed|reversed, ans2)
        ));

        BOOST_FOREACH (int i, src|uniqued|reversed)  {
            std::cout << i << ',';
        }
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
