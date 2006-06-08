#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/null_terminate_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/begin_end.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/counting_range.hpp>
#include <pstade/oven/equal.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        char str[] = "hello range";

        BOOST_CHECK( oven::equal(oven::make_null_terminate_range(str), str) );
        BOOST_CHECK( oven::equal(str|oven::null_terminated, str) );
    }

    {
        const int str[] = { 1, 2, 3, 0, 4, 5 };
        BOOST_CHECK( oven::equal(oven::make_null_terminate_range(str), boost::begin(oven::make_counting_range(1, 4))) );
        BOOST_CHECK( oven::equal(str|oven::null_terminated, oven::make_counting_range(1, 4)|oven::begun) );
    }

    {
        char str[] = "hello\0secret";
        std::vector<char> vec;
        
        BOOST_FOREACH( char ch, str|oven::null_terminated) {
            vec.push_back(ch);
        }
        
        BOOST_CHECK( oven::equals( vec, "hello"|oven::null_terminated ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
