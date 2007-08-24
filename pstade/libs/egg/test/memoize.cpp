#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/memoize.hpp>
#include <pstade/unit_test.hpp>


#include <iostream>


namespace egg = pstade::egg;
using namespace egg;


struct fib_block
{
    typedef int argument_type;
    typedef int result_type;

    template<class Recur>
    int operator()(Recur rec, int x) const
    {
        return x <= 1 ? 1 : rec(x-1) + rec(x-2);
    }
};


void pstade_unit_test()
{
    {
        BOOST_CHECK(memoize(fib_block())(10) == 89);
    }
}
