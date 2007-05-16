#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/to_string_to.hpp>


#include <string>


void test()
{
    using namespace pstade;

    {
        BOOST_CHECK( pstade::string_to<int>("10") == 10 );

        int i = "10"|unstrung;
        BOOST_CHECK( i == 10 );
    }

    {
        BOOST_CHECK( pstade::string_to<int>(std::string("10")) == 10 );

        int i = std::string("10")|unstrung;
        BOOST_CHECK( i == 10 );
    }

    {
        BOOST_CHECK( (10|to_string) == "10" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
