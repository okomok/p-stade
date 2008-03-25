

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/memoize.hpp>


#include "./egg_example.hpp"


//[code_example_memoize
struct T_fib
{
    typedef int result_type;

    template<class Fixed>
    int operator()(Fixed f, int x) const
    {
        return x <= 1 ? 1 : f(x-1) + f(x-2);
    }

    int operator()(int x) const
    {
        return (*this)(*this, x);
    }
};

T_fib const fib = {};

void egg_example()
{
    BOOST_CHECK( fib(30) == 1346269 );
    BOOST_CHECK( memoize(fib)(30) == 1346269 );
}
//]
