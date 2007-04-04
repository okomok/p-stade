#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/typeof/typeof.hpp>

namespace lambda = boost::lambda;
using namespace pstade::oven;

void test()
{
    BOOST_AUTO(factorials,
        expression(counting_from(1)|scanned(1, regular(lambda::_1 * lambda::_2))) );

    int const answer[] = { 1,1,2,6,24,120,720,5040,40320,362880 };
    BOOST_CHECK( equals(factorials|taken(10), answer) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
