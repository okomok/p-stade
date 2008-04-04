

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/curry.hpp>
#include <boost/egg/static.hpp>
#include <functional> // minus


#include "./egg_example.hpp"


//[code_example_curry
struct base_my_minus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x - y;
    }
};

static_< result_of_<T_curry2(base_my_minus)> >::type
    const curried_minus = {{}};

void egg_example()
{
    BOOST_CHECK( curried_minus(4)(9) == -5 );
    BOOST_CHECK( curry2(base_my_minus())(4)(9) == -5 );
}
//]
