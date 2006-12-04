#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/auto_castable.hpp>


#include <string>
#include <pstade/lexical_cast.hpp>
#include <pstade/pipable.hpp>


PSTADE_AUTO_CASTABLE(lexical, pstade::lexical_cast_fun)
PSTADE_PIPABLE(lexicalized, lexical_fun)


void test()
{
    {
        int to = ::lexical(std::string("3"));
        BOOST_CHECK( to == 3 );
    }
    {
        std::string to = ::lexical(512);
        BOOST_CHECK( to == "512" );
    }
    {
        int to = std::string("3")|::lexicalized;
        BOOST_CHECK( to == 3 );
    }
    {
        std::string to = 512|::lexicalized;
        BOOST_CHECK( to == "512" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
