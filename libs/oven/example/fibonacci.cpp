#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_TESTS_DONT_CALL_DISTANCE
#include "../test/detail/v1_tests.hpp"


#include <string>
#include <iostream>
#include <pstade/oven.hpp>
#include <pstade/egg/to_value.hpp>
#include <pstade/tuple.hpp> // tuple_pack
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <pstade/oven/recursion.hpp>


namespace assign = boost::assign;
namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


void pstade_unit_test()
{
    int const howMany = 30;
    int answer[howMany] = {1,1,2,3,5,8,13,21,34,55,89,144,233,377, 610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040};
    std::vector<int> expected = answer|copied;

    {
        typedef any_range<int const&, boost::forward_traversal_tag> range_t;
        range_t fibs;
        memo_table tb;
        int const start[] = { 1, 1 };
        fibs =
            start
                | transformed(pstade::egg::to_value)
                | jointed(
                    boost::make_tuple(recursion(fibs), recursion(fibs)|dropped(1))|
                        zipped_with(regular(lambda::_1 + lambda::_2))
                  )
                | memoized(tb)
        ;

        BOOST_CHECK( oven::test_Forward_Readable(fibs|taken(howMany), expected) );
    }
}

