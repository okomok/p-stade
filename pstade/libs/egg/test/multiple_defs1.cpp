// #include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./egg_all.hpp"
#undef PSTADE_EGG_DETAIL_EGG_HPP
#undef PSTADE_EGG_DETAIL_EGG_PENDING_HPP
#include "./egg_all.hpp"


#include <pstade/minimal_test.hpp>


#include <pstade/egg/alias.hpp>


using namespace pstade::egg;
using pstade::egg::plus;


// warning check should be shown in IDE.
struct no_assignment
{
    int const &x;
};


void pstade_minimal_test()
{
    int x;
    no_assignment a = { x };
}
