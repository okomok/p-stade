

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/curry.hpp>
#include <boost/egg/static.hpp>
#include <functional>


#include "./egg_example.hpp"

//[code_example_function_adaptors
int plusfun(int i, int j)
{
    return i + j;
};

static_< result_of_<T_curry2(std::plus<int>)> >::type const splus = {{}}; /*< __STATIC_INITIALIZATION__ for "stateless" functions >*/
result_of_<T_curry2(int(*)(int, int))>::type const mplus = BOOST_EGG_CURRY2(&plusfun); /*< __STATIC_INITIALIZATION__ for "stateful" functions >*/

void egg_example()
{
    result_of_<T_curry2(std::plus<int>)>::type dplus = curry2(std::plus<int>()); /*< /dynamic initialization/ >*/

    BOOST_CHECK( splus(1)(2) == 3 );
    BOOST_CHECK( mplus(1)(2) == 3 );
    BOOST_CHECK( dplus(1)(2) == 3 );
}
//]
