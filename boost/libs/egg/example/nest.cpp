

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

    int _6_ = 6, _1_ = 1, _3_ = 3, _9_ = 9;

// Lv: 0     1      2      3
    // \x -> (\y -> (\z -> foo(y,z,x)))
    BOOST_CHECK( nest3(foo)(nest1(_1), nest2(_1), nest0(_1)) /*< Works as `curry3`. >*/
        (_3_)(_6_)(_1_) == foo(6,1,3) );

    // \x -> apply(\y -> minus(x,y), plus(x,3))
    BOOST_CHECK( nest1(apply)(nest2(minus)(nest0(_1), nest1(_1)), nest1(plus)(nest0(_1), 3)) /*< By the definition, `nest1(apply)` has the same semantics as `lazy(apply)`. >*/
        (_9_) == minus(9, plus(9,3))  );
}
//]
