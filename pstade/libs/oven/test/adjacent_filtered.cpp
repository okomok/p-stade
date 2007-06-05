#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/adjacent_filtered.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <pstade/oven/regular.hpp>
#include <pstade/oven/identities.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


struct is_divisor
{
    bool operator()(int x, int y) const
    { return (y % x) == 0; }
};


struct not_equal_to
{
    bool operator()(int x, int y) const
    { return x != y; }
};


void pstade_minimal_test()
{
    {
        int a[] = { 2, 2, 4, 4, 8, 8, 40, 80 };
        int b[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
        test::adaptor_forward_constant_int    (lambda::bind(make_adjacent_filtered, lambda::_1, ::is_divisor()), a, b);
        test::adaptor_single_pass_readable_int(lambda::bind(make_adjacent_filtered, lambda::_1, ::is_divisor()), a, b|identities(in_single_pass));
    }
    {
        int a[] = { 2, 4, 6, 8, 10, 20, 40, 80, 120 };
        int b[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
        test::adaptor_forward_constant_int    (lambda::bind(make_adjacent_filtered, lambda::_1, ::not_equal_to()), a, b);
        test::adaptor_single_pass_readable_int(lambda::bind(make_adjacent_filtered, lambda::_1, ::not_equal_to()), a, b|identities(in_single_pass));
    }
    {
        int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
        int b[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
        test::adaptor_forward_constant_int    (lambda::bind(make_adjacent_filtered, lambda::_1, ::not_equal_to()), a, b);
        test::adaptor_single_pass_readable_int(lambda::bind(make_adjacent_filtered, lambda::_1, ::not_equal_to()), a, b|identities(in_single_pass));
    }
    {
        test::adaptor_emptiness_int           (lambda::bind(make_adjacent_filtered, lambda::_1, ::not_equal_to()));
    }
    {
        int a[] = { 2, 4, 6, 8, 10, 20, 40, 80, 120 };
        int b[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
        test::adaptor_forward_constant_int    (lambda::bind(make_adjacent_filtered, lambda::_1, regular(lambda::_1 != lambda::_2)), a, b);
        test::adaptor_single_pass_readable_int(lambda::bind(make_adjacent_filtered, lambda::_1, regular(lambda::_1 != lambda::_2)), a, b|identities(in_single_pass));
    }
}
