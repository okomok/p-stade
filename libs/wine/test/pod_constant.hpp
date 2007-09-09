#ifndef PSTADE_LIBS_WINE_TEST_POD_CONSTANT_HPP
#define PSTADE_LIBS_WINE_TEST_POD_CONSTANT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


struct A { };
struct B { A a; int i; };

PSTADE_POD_CONSTANT((A), g_a1) = { };
PSTADE_POD_CONSTANT((B), g_b1) = { { }, 3 };

// compare
A const g_a2 = { };
B const g_b2 = { { }, 3 };


// suppress warning check under gcc4 which says warning around templates.
template<class B>
struct ff
{
    B b;
};

PSTADE_POD_CONSTANT((ff<B>), g_ffb) = {{}};


#endif
