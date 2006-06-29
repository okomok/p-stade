#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/file_range.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        file_range<> frng("non-exist.file");
        BOOST_CHECK(( boost::empty(frng) ));
        BOOST_CHECK(( !frng.is_open() ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
