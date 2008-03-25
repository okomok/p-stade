

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./egg_test.hpp"


template<class A>
void foo(A const&) {}

template<class A>
void foo(A&) {}

namespace my {

    int bar(int) { return 0; }

}

int buz(char) { return 0; }


void egg_test()
{
    {
        ::foo(my::bar);
        ::foo(::my::bar);
        ::foo(buz);
        ::foo(::buz);
    }
}
