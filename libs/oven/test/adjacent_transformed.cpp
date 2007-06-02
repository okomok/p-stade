#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/adjacent_transformed.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


#include <pstade/functional.hpp>
#include <pstade/compose.hpp>
#include <pstade/result_of_lambda.hpp>
#include <pstade/oven/const_refs.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


int& get_right(int& l, int& r)
{
    return r;
}


void pstade_minimal_test()
{
    {
        int b[] = { 1,2,3,4,5,6,7,8,9,10 };
        int a[] = { 3,5,7,9,11,13,15,17,19 };
        test::adaptor_random_access_constant_int(pstade::compose(make_const_refs, lambda::bind(make_adjacent_transformed, lambda::_1, pstade::plus)), a, b);
    }
    {
        int a[] = { 1,3,6,1,9,6,1,2,3,1 };
        int b[] = { 6,1,3,6,1,9,6,1,2,3,1 };
        test::random_access_swappable(*test::new_vector<int>(b)|adjacent_transformed(&::get_right), a);

        // Notice that once a range of NonCopyable type is transformed, it is not swappable.
    }
    {
        int const b[] = { 1 };
        test::emptiness(b|adjacent_transformed(pstade::plus));
    }
}
