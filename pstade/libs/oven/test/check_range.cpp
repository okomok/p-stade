#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/check_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/arg.hpp>
#include <pstade/unused.hpp>
#include <pstade/if_debug.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("hello, check_range");
        std::vector<char> expected = rng|copied;
        BOOST_CHECK(oven::test_RandomAccess_Readable_Writable(rng|checked, expected));
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

    {
        pstade::unused(
            std::string()
PSTADE_IF_DEBUG(| checked)
                | pstade::argued,
            12
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
