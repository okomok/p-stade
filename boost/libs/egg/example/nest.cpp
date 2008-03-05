

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/nest.hpp>
#include <functional> // plus
#include <boost/egg/apply.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


int foo(int i, int j, int k)
{
    return i + j - k;
}


//[code_example_nest
void egg_example()
{
    using bll::_1;
    using bll::_2;
    std::plus<int> plus;
    std::minus<int> minus;

    // \x -> (\y -> (\z -> foo(y,z,x)))
    BOOST_CHECK( nest3(foo)(lv1(_1), lv2(_1), lv0(_1)) /*< Works as `curry3`. >*/
        (3)(6)(1) == foo(6,1,3) );

    // \x -> apply(\y -> minus(x,y), plus(x,3))
    BOOST_CHECK( nest1(apply)(nest2(minus)(lv0(_1), lv1(_1)), nest1(plus)(lv0(_1), 3)) /*< By the definition, `nest1` has the same semantics as __EGG_LAZY__. >*/
        (9) == minus(9, plus(9,3))  );
}
//]
