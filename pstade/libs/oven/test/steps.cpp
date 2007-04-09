#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/steps.hpp>


#include <pstade/oven/functions.hpp>
#include <pstade/oven/identities.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int src[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };

    {
        std::vector<int> expected = src|copied;

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            src|steps(1),
            expected
        ) );

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            src|identities(in_forward)|steps(1),
            expected
        ) );
    }
    {
        int const ans[] = { 0,3,6,9,12,15,18 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            src|steps(3),
            expected
        ) );

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            src|identities(in_forward)|steps(3),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::test_empty(std::string()|steps(1)) );
        BOOST_CHECK( oven::test_empty(std::string()|steps(3)) );
        BOOST_CHECK( distance(src|steps(90)) == 1 );
    }
    {
        int const answer[] = { 0, 40, 80 };
        BOOST_CHECK( equals(
            counting(0, 100)|steps(10)|steps(4),
            answer
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
