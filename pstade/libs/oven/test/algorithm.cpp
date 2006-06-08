#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/find.hpp>


#include <string>


struct is_c
{
    bool operator()(char ch) const
    { return ch == 'c'; }
};


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string src1("abcde");
    std::string src2("abcde");

    { // equals
        BOOST_CHECK( oven::equals(src1, src2) );
    }

    { // copy
        std::string tmp(src1);
        std::string::iterator it = boost::begin(tmp);
        oven::copy(src1, it);
        BOOST_CHECK( oven::equals(src1, tmp) );
    }

    { // find
        BOOST_CHECK( oven::find_if(src1, is_c()) == oven::find(src1, 'c') );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
