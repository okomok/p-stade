#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/always.hpp>


#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 1,2,5,1,2,3,5,1,1 };
        int b[] = { 5,1,3,5,1,2,5 };
        test::random_access_constant(b|always(a), a);
        test::random_access_swappable(b|always(*test::new_vector<int>(a)), a);
    }
}
