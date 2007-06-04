#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/duplicates.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


#include <string>
#include <pstade/oven/identities.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    {
        int a[] = { 6,1,3,8,1,2,9,4 };
        int b[] = { 6,6,6,0,6,6,1,1,3,3,3,8,8,8,8,8,8,1,1,1,2,2,9,9,4,4,4,4,4 };

        test::adaptor_forward_constant_int(
            lambda::bind(make_duplicates, lambda::_1),
            a, b
        );

        test::adaptor_forward_swappable_int(
            lambda::bind(make_duplicates, lambda::_1),
            a, b
        );

        test::single_pass_readable(
            b|identities(in_single_pass)|duplicates,
            a
        );
    }
    {
        test::adaptor_emptiness_int(
            lambda::bind(make_duplicates, lambda::_1)
        );
    }
}
