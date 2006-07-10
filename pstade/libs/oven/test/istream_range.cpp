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
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/algorithms.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string result;
        std::stringstream ss;
        ss << "hello,istream_range!";
    #if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        oven::copy(oven::make_istream_range<char>(ss), garlic::back_inserter(result));
    #else
        oven::copy(oven::make_istream_range<char>(ss), std::back_inserter(result));
    #endif
        BOOST_CHECK(( oven::equals(result, std::string("hello,istream_range!")) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
