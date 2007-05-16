#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/front.hpp>
#include <pstade/oven/back.hpp>


#include <string>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("f12344513215b");
        BOOST_CHECK( front(str) == 'f' );
        BOOST_CHECK( back(str)  == 'b' );
        BOOST_CHECK( value_front(str) == 'f' );
        BOOST_CHECK( value_back(str)  == 'b' );

        front(str) = 'g';
        back(str) = 'c';
        BOOST_CHECK( str == "g12344513215c" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
