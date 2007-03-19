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
#include <pstade/oven/is_heap.hpp>
#include <pstade/oven/is_sorted.hpp>


#include <algorithm> // make_heap
#include <string>
#include <boost/range.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


PSTADE_TEST_IS_RESULT_OF((bool), op_equals(std::string&, std::string&))
PSTADE_TEST_IS_RESULT_OF((range_difference<std::string>::type), op_distance(std::string&))
PSTADE_TEST_IS_RESULT_OF((bool), op_is_sorted(std::string&))
PSTADE_TEST_IS_RESULT_OF((bool), op_is_heap(std::string&))


void test()
{
    std::string src1("abcde");
    std::string src2("abcde");
    {
        BOOST_CHECK( equals(src1, src2) );
        BOOST_CHECK( equals(src1|identities(in_single_pass), src2|identities(in_single_pass)) );
    }
    {
        BOOST_CHECK( distance(src1) == 5 );
        BOOST_CHECK( distance(src1|identities(in_single_pass)) == 5 );
    }
    {
        int const rng[] = { 5,6,7,8,9,10,11,13,16 };
        int const rng_[]= { 0,3,7,1,3,6,1,3,3,6,1 };
        BOOST_CHECK( is_sorted(rng) );
        BOOST_CHECK( !is_sorted(rng_) );
    }
    {
        int rng[] = { 5,6,1,7,8,9,10,2,11,13,16 };
        BOOST_CHECK( !is_heap(rng) );
        std::make_heap(boost::begin(rng), boost::end(rng));
        BOOST_CHECK( is_heap(rng) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
