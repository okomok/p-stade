#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/spirit/phoenix/algorithm.hpp>
#include <boost/spirit/phoenix/core.hpp>


void test()
{
    std::vector<int> vec;
    boost::phoenix::sort(boost::phoenix::arg1)(vec);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
