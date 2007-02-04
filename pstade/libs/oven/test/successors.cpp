#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/successors.hpp>


#include <pstade/oven/functions.hpp>


struct increment
{
    template< class Iter >
    Iter operator()(Iter king, Iter last) const
    {
        BOOST_CHECK(king != last);

        (void)last;
        return ++king;
    }
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int const src[] = { 1,3,5,7,9,12,3,1,2,3,4,5,6,1,2,3,23 };

    {
        std::vector<int> expected = src|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            src|successors(::increment()),
            expected
        ) );

    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
