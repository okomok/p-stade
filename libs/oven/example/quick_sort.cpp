#include <pstade/vodka/drink.hpp>
#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Caution:
//
// This is NO quick!


#include <iostream>
#include <pstade/oven.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/oven/sugar.hpp>

namespace lambda = boost::lambda;
using namespace pstade::oven;


typedef
    any_range<int&, boost::forward_traversal_tag>
range;


range quick_sort(range rng)
{
    if (!rng)
        return rng;
    else {
        int& x = front(rng);
        range xs = rng|dropped(1);

        return
            quick_sort( xs|filtered(regular(lambda::_1 < x)) )
            >> single(x)
            >> quick_sort( xs|filtered(regular(lambda::_1 >= x)) );
        ;
    }
}


void pstade_unit_test()
{
    std::vector<int> v = initial_values(3,2,5,4,6,1);

    std::cout << quick_sort(range(v)) << std::endl;

    BOOST_CHECK( equals(
        quick_sort(range(v)),
        initial_values(1,2,3,4,5,6)
    ) );
}
