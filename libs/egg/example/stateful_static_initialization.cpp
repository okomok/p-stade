

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pipable.hpp>
#include <boost/egg/curry.hpp>


#include "./egg_example.hpp"


int foo(int i, int j, int k)
{
    return i - j + k;
}

//[code_example_stateful_static_initialization
typedef result_of_<T_pipable(int(*)(int,int,int))>::type T_pfoo;
T_pfoo const pfoo = BOOST_EGG_PIPABLE(&foo);

typedef result_of_<T_curry2(T_pfoo)>::type T_cfoo;
T_cfoo const cfoo = BOOST_EGG_CURRY2_L BOOST_EGG_PIPABLE(&foo) BOOST_EGG_CURRY2_R; /*< A macro invocation must be sandwiched by `_L` and `_R` form.  >*/

void egg_example()
{
    BOOST_CHECK( (1|pfoo(2,3)) == foo(1,2,3) );
    BOOST_CHECK( (1|cfoo(2)(3)) == foo(1,2,3) );
}
//]
