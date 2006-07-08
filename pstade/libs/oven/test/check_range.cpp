#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/check_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/algorithms.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string str("hello, check_range");
        BOOST_CHECK(oven::equals(str, str|checked));
    }

    {
        std::string in("012345");
        std::string out("01234");

        bool thrown = false;

        try {
            oven::equal( in, boost::begin(out|checked) );
        }
        catch (check_error const& ) {
            thrown = true;
        }

        BOOST_CHECK(thrown);
        thrown = false;

        (boost::begin(out|checked) + 5) - 5;

        try {
            boost::begin(out|checked) + 6;
        }
        catch (check_error const& ) {
            thrown = true;
        }

        BOOST_CHECK(thrown);
        thrown = false;

        try {
            (boost::begin(out|checked) + 5) - 6;
        }
        catch (check_error const& ) {
            thrown = true;
        }

        BOOST_CHECK(thrown);
        thrown = false;
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
