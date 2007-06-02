#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/steps.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


#include <pstade/oven/equals.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    {
        int a[] = { 6,1,34,5,1,6,4,2,212,5,6,76,4,7,2,889,52,1,3,7,0,2,12 };
        int b[] = { 6,1,34,5,1,6,4,2,212,5,6,76,4,7,2,889,52,1,3,7,0,2,12 };
        test::adaptor_forward_constant_int (lambda::bind(make_steps, lambda::_1, 1), a, b);
        test::adaptor_forward_swappable_int(lambda::bind(make_steps, lambda::_1, 1), a, b);
    }
    {
        int a[] = { 0,3,6,9,12,15,18 };
        int b[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
        test::adaptor_forward_constant_int (lambda::bind(make_steps, lambda::_1, 3), a, b);
        test::adaptor_forward_swappable_int(lambda::bind(make_steps, lambda::_1, 3), a, b);
    }
    {
        test::adaptor_emptiness_int        (lambda::bind(make_steps, lambda::_1, 1));
        test::adaptor_emptiness_int        (lambda::bind(make_steps, lambda::_1, 3));
        test::adaptor_emptiness_int        (lambda::bind(make_steps, lambda::_1, 100));
    }
    {
        int a[] = { 0 };
        int b[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
        BOOST_CHECK( equals(b|steps(100), a) );
    }
}
