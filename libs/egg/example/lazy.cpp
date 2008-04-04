

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/lazy.hpp>
#include <boost/egg/static.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_lazy
struct base_my_plus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

static_< result_of_<T_lazy(base_my_plus)> >::type
    const my_Plus = {{}};

void egg_example()
{
    using bll::_1;
    using bll::_2;

    BOOST_CHECK( my_Plus(_1, 3)(bll::make_const(2)) == 5 ); /*< Boost1.35 or later won't require `make_const`. >*/

    int two = 2, four = 4;
    BOOST_CHECK( my_Plus(my_Plus(_1, 3), my_Plus(_2, _1))
        (two, four) == (2+3)+(4+2) );
}
//]
