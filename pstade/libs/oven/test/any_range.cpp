#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/any_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/ranges.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


void test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("8frj91j81hf891y2");
        std::vector<char> expected = rng|copied;

        any_range<char, boost::random_access_traversal_tag> any_(rng);
        any_ = rng;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            any_,
            expected
        ) );
    }
    {
        std::string str;
        any_range<char, boost::random_access_traversal_tag> any_rng(str|identities);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
