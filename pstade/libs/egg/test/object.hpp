#ifndef PSTADE_LIBS_EGG_TEST_OBJECT_HPP
#define PSTADE_LIBS_EGG_TEST_OBJECT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/object.hpp>


struct A { };
struct B { A a; int i; };

PSTADE_EGG_OBJECT((A), g_a1) = { };
PSTADE_EGG_OBJECT((B), g_b1) = { { }, 3 };

// compare
A const g_a2 = { };
B const g_b2 = { { }, 3 };


#endif
