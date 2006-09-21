#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/distance.hpp>
#include <pstade/oven/equals.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/egg/function.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string src1("abcde");
    std::string src2("abcde");

    { // equals
        BOOST_CHECK( oven::equals(src1, src2) );
    }

    { // distance
        BOOST_CHECK( oven::distance(src1) == 5 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
