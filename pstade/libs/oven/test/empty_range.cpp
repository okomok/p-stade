#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/empty_range.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        empty_range<int> rng;
        test::emptiness(rng);
    }
    {
        test::emptiness(empty_range<int>());
        test::equality( empty_range<char>(), empty_range<char>() );
    }
}
