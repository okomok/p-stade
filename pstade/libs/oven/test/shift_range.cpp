#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/shift_range.hpp>


#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int A[] = { 0,1,2,3,4,5,6,7,8,9 };
    {
        BOOST_CHECK( oven::equals(
            boost::make_iterator_range(A+1,A+4)|shifted(1),
            boost::make_iterator_range(A+2,A+5)
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
