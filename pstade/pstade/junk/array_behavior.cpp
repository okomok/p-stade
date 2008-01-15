#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


#include <cstddef>


template<class X>
struct gunk;

template<class T, std::size_t N>
struct gunk< T[N] >
{
    typedef int type;
};


template<class X>
typename gunk<X const>::type foo(X const& x)
{
    return 0;
}


void pstade_minimal_test()
{
    {
        int a[3] = {};  foo(a);
    }
    {
        int const a[3] = {};  foo(a);
    }
}
