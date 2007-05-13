#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/undefine_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string()|undefined;

        bool thrown = false;

        try {
            oven::distance(std::string()|undefined);
        }
        catch (undefine_error const& ) {
            thrown = true;
        }

        BOOST_CHECK(thrown);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
