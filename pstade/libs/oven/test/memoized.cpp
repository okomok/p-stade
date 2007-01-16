#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/memoized.hpp>


#include <string>
#include <sstream>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/istream_range.hpp>
#include <pstade/oven/regularized.hpp>

#include <iterator>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    namespace bll = boost::lambda;

    {
        std::string ans("18284610528192");
        std::stringstream ss;
        ss << ans;
        std::vector<char> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            oven::make_istream_range<char>(ss)|memoized,
            expected
        ) );
    }

    {
        std::string src("axaxaxbxbxbx");
        std::string s1; // snapshot
        std::string s2;
        std::string answer("bbb");

        BOOST_CHECK((
            oven::equals(answer,
                src |
                    filtered(bll::_1 != 'x') |
                    regularized |
                    memoized |
                    copied_out(std::back_inserter(s1)) |
                    filtered(bll::_1 != 'a') |
                    regularized |
                    memoized |
                    copied_out(std::back_inserter(s2))
            )
        ));

        BOOST_CHECK( s1 == "aaabbb" );
        BOOST_CHECK( s2 == answer );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
