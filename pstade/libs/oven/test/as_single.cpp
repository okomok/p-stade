#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/as_single.hpp>


#include <memory>
#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>
#include <pstade/new_delete.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string ans("a");

    {
        BOOST_CHECK( oven::equals('a'|as_single, ans) );
    }
    {
        BOOST_CHECK( oven::equals(as_single('a'), ans) );
    }
    {
        char ch = 'a';
        BOOST_CHECK( oven::equals(oven::as_single(ch), ans) );
    }

    {
        BOOST_CHECK( oven::equals(new char('a')|as_shared_single, ans) );
    }

    {
        BOOST_CHECK( oven::equals(as_shared_single(pstade::op_new_auto<char>()('a')), ans) );
        BOOST_CHECK( oven::equals(pstade::op_new_auto<char>()('a')|as_shared_single, ans) );
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
