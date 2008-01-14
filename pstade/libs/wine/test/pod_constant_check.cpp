#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/minimal_test.hpp>


struct B {};
struct D : B {};


PSTADE_POD_CONSTANT((D), d) = D();


inline void check_(...) {}
void check_pod_()
{
    check_(D());
}


void pstade_minimal_test()
{
}
