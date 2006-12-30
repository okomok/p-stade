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


#include <pstade/value.hpp>
#include <string>
#include <boost/utility/result_of.hpp>
#include <utility>


using namespace pstade;


std::pair<int, char> foo()
{
    return constructor(3, 'c');
}


// Note:
// GCC3.4 would fail if 'std::pair' had a unary template constructor,
// because GCC3.4 prefers direct-initialization to copy-initialization
// in the case of default argument syntax. This must be the bug of GCC3.4.
void bar(std::pair<int, char> p = constructor(3, 'c'))
{
    BOOST_CHECK(p == std::make_pair(3, 'c'));
}


void test()
{
    {
        boost::result_of<op_construct<std::string>(char const*)>::type
            x = op_construct<std::string>()("hello"|to_value);
        BOOST_CHECK( x == std::string("hello") );
    }
    {
        std::string x = constructor("hello");
        BOOST_CHECK( x == std::string("hello") );
    }
    {
        std::string x = constructor;
    }
    {
        BOOST_CHECK(foo() == std::make_pair(3, 'c'));
    }
    {
        bar();
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
