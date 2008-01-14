#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/filtered.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


struct is_positive
{
    // no result_type

    bool operator()(int x) const
    { return 0 < x; }
};


void pstade_minimal_test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 9,1,3,7,4,31,1,76,9,2,3 };
        int b[] = { -1,0,9,-3,-6,1,3,7,4,31,-2,1,-2,76,-1,9,-6,2,3 };

        test::adaptor_bidirectional_constant_int(
            lambda::bind(make_filtered, lambda::_1, is_positive()),
            a, b
        );

        test::adaptor_bidirectional_swappable_int(
            lambda::bind(make_filtered, lambda::_1, is_positive()),
            a, b
        );
    }
}
