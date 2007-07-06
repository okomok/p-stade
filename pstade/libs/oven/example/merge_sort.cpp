#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <pstade/oven/oven.hpp>
#include <boost/tuple/tuple.hpp>

namespace lambda = boost::lambda;
using namespace pstade::oven;


typedef
    any_range<int const&, boost::forward_traversal_tag>
range;


range merge_sort(range rng)
{
    typedef pstade::result_of<op_distance(range&)>::type diff_t;

    diff_t const d = distance(rng);
    if (d < 2)
        return rng;
    else {
        pstade::result_of<op_make_split_at(range&, diff_t)>::type
            xs_ys = make_split_at(rng, d/2);

        return make_merged(
            merge_sort(xs_ys.first),
            merge_sort(xs_ys.second)
        );
    }
}


void pstade_unit_test()
{
    std::vector<int> v = initial_values(7,3,2,6,5,9,4,8,1);

    std::cout << merge_sort(range(v)) << std::endl;

    BOOST_CHECK( equals(
        merge_sort(range(v)),
        initial_values(1,2,3,4,5,6,7,8,9)
    ) );
}
