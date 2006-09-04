#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/istream_range.hpp>


#include <iterator>
#include <sstream>
#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/copy_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string ans("hello,istream_range!");
        std::stringstream ss;
        ss << ans;
        std::string result = oven::make_istream_range<char>(ss)|copied;
        BOOST_CHECK(( oven::equals(result, ans) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
