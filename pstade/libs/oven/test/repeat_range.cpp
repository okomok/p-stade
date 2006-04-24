#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/repeat_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/reverse_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string ans("xyzxyzxyz");
        std::string src("xyz");
        repeat_range<std::string> vrng1(src, 3);
        BOOST_CHECK( oven::equals(vrng1.source(), src) );

        repeat_range<std::string> vrng2 = vrng1;
        BOOST_CHECK( oven::equals(vrng1, ans) );
        BOOST_CHECK( oven::equals(vrng2, ans) );

        vrng2 = oven::make_repeat_range(src, std::size_t(3));
        BOOST_CHECK( oven::equals(vrng2, ans) );
    }

    {
        BOOST_CHECK( oven::equals(
            std::string("xyz")|oven::repeated(3),
            std::string("xyzxyzxyz")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
