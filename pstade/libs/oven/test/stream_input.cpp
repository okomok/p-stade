#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/stream_input.hpp>


#include <iterator>
#include <sstream>
#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/copy_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string ans("hello,istream_range!");
        std::stringstream ss;
        ss << ans;
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::stream_input<char>(ss),
            expected
        ) );
    }

    {
        std::string ans("hello,istream_range!");
        std::stringstream ss;
        ss << ans;
        std::string result = oven::stream_input<char>(ss)|copied;
        BOOST_CHECK(( oven::equals(result, ans) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
