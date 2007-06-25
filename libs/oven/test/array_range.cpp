#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/array_range.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <pstade/oven/distance.hpp>
#include <algorithm> // copy
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 1,3,5,1,3,5,13,6,1,7,3,1,4,4 };
        array_range<int> b(distance(a));
        std::copy(boost::begin(a), boost::end(a), boost::begin(b));
        test::random_access_constant(b, a);
        test::random_access_swappable(b, a);
    }
}
