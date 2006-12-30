#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <pstade/construct.hpp>


#include <string>
#include <utility>


using namespace pstade;


std::pair<int, char> foo()
{
    return constructor(3, 'c');
}


void test()
{
    {
        BOOST_CHECK( construct<std::string>()("hello") == std::string("hello") );
    }
    {
        std::string str = constructor;
    }
    {
        BOOST_CHECK(foo() == std::make_pair(3, 'c'));
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
