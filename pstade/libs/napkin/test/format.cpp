#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/napkin.hpp>


#include <sstream>
#include <string>
#include <vector>
#include <pstade/oven/equal.hpp>
#include <boost/format.hpp>


void test()
{
    using namespace pstade;

    {
        std::stringstream sout;

        napkin::ostream os1(sout);
        os1 << boost::format("%2% %1%") % 36 % 77;
        BOOST_CHECK( sout.str() == "77 36" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
