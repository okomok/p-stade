#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/equals.hpp>


#include <string>
#include <boost/utility/result_of.hpp>
#include <pstade/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


PSTADE_TEST_IS_RESULT_OF((bool), op_equals(std::string&, std::string&))
PSTADE_TEST_IS_RESULT_OF((range_difference<std::string>::type), op_distance(std::string&))


void test()
{
    std::string src1("abcde");
    std::string src2("abcde");
    {
        boost::result_of<op_equals(std::string&, std::string&)>::type b = equals(src1, src2);
        BOOST_CHECK( b );
    }
    {
        boost::result_of<op_distance(std::string&)>::type d = distance(src1);
        BOOST_CHECK( d == 5 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
