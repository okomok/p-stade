#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


struct T_foo
{
    template< class Result, class A0 >
    Result call(A0& a0) const
    {
        return Result();
    }

    template< class Result, class A0 >
    Result call(A0 const&) const
    {
        return Result();
    }
};


void pstade_minimal_test()
{
    double const d = 0;
    T_foo().call<int>(d);
}
