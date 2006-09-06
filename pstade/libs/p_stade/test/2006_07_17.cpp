#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/concepts.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


#include <boost/iterator/new_iterator_tests.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <pstade/oven/regularize_iterator.hpp>


#include <vector>


template< class Iterator >
void foo(Iterator x)
{
    Iterator y;
    y = x;
}


void test()
{
    std::string rng("axax");

/* error:
    ::foo(
        boost::make_filter_iterator(
            boost::lambda::_1 != 'x',
            boost::begin(rng),
            boost::end(rng)
        )
    );
*/

    ::foo( pstade::oven::make_regularize_iterator(
        boost::make_filter_iterator(
            boost::lambda::_1 != 'x',
            boost::begin(rng),
            boost::end(rng)
        )
    ) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
