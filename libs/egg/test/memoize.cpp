#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/memoize.hpp>
#include <pstade/unit_test.hpp>


#include <boost/progress.hpp>
#include <iostream>


namespace egg = pstade::egg;
using namespace egg;


struct fib_block
{
    typedef int result_type;

    template<class Fixed>
    int operator()(Fixed f, int x) const
    {
        return x <= 1 ? 1 : f(x-1) + f(x-2);
    }
};


void pstade_unit_test()
{
    {
        BOOST_CHECK(memoize(fib_block())(10) == 89);
    }
    {
        boost::progress_timer t;
        BOOST_CHECK(memoize(fib_block())(30) == 1346269);
    }
    {
        boost::progress_timer t;
        BOOST_CHECK(fix(curry2(fib_block()))(30) == 1346269);
    }
}
