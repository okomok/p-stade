#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/istream_range.hpp>


#include <sstream>
#include <string>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string result;
        std::stringstream ss;
        ss << "hello,istream_range!";
        oven::copy(oven::make_istream_range<char>(ss), garlic::back_inserter(result));
        BOOST_CHECK(( oven::equals(result, std::string("hello,istream_range!")) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
