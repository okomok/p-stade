#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/adjacent_transformed.hpp>


#include <iostream>
#include <pstade/oven/functions.hpp>
#include <pstade/functional.hpp>
#include <pstade/oven/const_lvalues.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/oven/regular.hpp>
#include <pstade/oven/algorithm.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int const src[] = { 1,2,3,4,5,6,7,8,9,10 };

    {
        int ans[] = { 3,5,7,9,11,13,15,17,19 };
        std::vector<int> expected = ans|copied;

        oven::copy(src|adjacent_transformed(pstade::plus), oven::to_stream(std::cout));

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            src |
                adjacent_transformed(pstade::plus) | const_lvalues,
            expected
        ) );

        BOOST_CHECK( oven::test_Forward_Readable(
            src | identities(boost::forward_traversal_tag()) |
                adjacent_transformed(pstade::plus) | const_lvalues,
            expected
        ) );

        namespace lambda = boost::lambda;
        BOOST_CHECK( oven::test_RandomAccess_Readable(
            src |
                adjacent_transformed(regular(lambda::_1 + lambda::_2)) | const_lvalues,
            expected
        ) );
    }
#if 0 // now empty range not supported.
    {
        std::vector<int> nothing;

        BOOST_CHECK( oven::test_empty(
            nothing |
                adjacent_transformed(pstade::plus)
        ) );

        BOOST_CHECK( oven::test_empty(
            nothing | identities(boost::forward_traversal_tag()) |
                adjacent_transformed(pstade::plus)
        ) );
    }
#endif
    {
        int const nothing[] = { 1 };

        BOOST_CHECK( oven::test_empty(
            nothing |
                adjacent_transformed(pstade::plus)
        ) );

        BOOST_CHECK( oven::test_empty(
            nothing | identities(boost::forward_traversal_tag()) |
                adjacent_transformed(pstade::plus)
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
