#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/concepts.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


#include <vector>


template< class Fun >
void foo(Fun f)
{
    Fun g(f);
    g = f;
}


void test()
{
    ::foo(boost::lambda::_1 != 'x');
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
