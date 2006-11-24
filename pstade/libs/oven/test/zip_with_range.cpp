#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/zip_with_range.hpp>


#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


struct plus
{
    typedef int result_type;

    int operator()(boost::tuple<int, int> t) const
    {
        return boost::get<0>(t) + boost::get<1>(t);
    }
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int xs[]  = { 0, 1, 2, 3, 4, 5, 6 };
        int ys[]  = { 1, 6, 1, 2, 7, 8, 3 };
        int ans[] = { 1, 7, 3, 5,11,13, 9 };
        std::vector<int> expected = ans|copied;

       BOOST_CHECK( oven::test_RandomAccess_Readable(
            xs|tied(ys)|zipped_with(::plus()),
            expected
        ) );
    }

    {
        int xs[]  = { 0, 1, 2, 3, 4, 5, 6 };
        int ys[]  = { 1, 6, 1, 2, 7, 8, 3 };
        int ans[] = { 1, 7, 3, 5,11,13, 9 };

        BOOST_CHECK( oven::equals(
            boost::tie(xs, ys)|zipped_with(::plus()),
            ans
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
