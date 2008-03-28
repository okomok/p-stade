

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/nest.hpp>
#include <functional> // plus
#include <boost/egg/apply.hpp>
#include <boost/utility/addressof.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


int foo(int i, int j, int k, int m)
{
    return i + j - k + m;
}

//[code_example_nest
int & second(int, int &j, int, int)
{
    return j;
}

void egg_example()
{
    using bll::_1;
    using bll::_2;
    std::plus<int> plus;
    std::minus<int> minus;

    int i6 = 6, i1 = 1, i3 = 3, i9 = 9;

// Lv: 0     1      2          3
    // \x -> (\y -> (\(z,w) -> foo(y,w,z,x))))
    BOOST_CHECK( nest3(foo)(_1_(_1), _2_(_2), _2_(_1), _0_(_1)) /*< `_M_` turns a placeholder into nested one. >*/
        (i3)(i6)(i1,i9) == foo(6,9,1,3) );

    // \x -> apply(\y -> minus(x,y), plus(x,3))
    BOOST_CHECK( nest1(apply)(nest2(minus)(_0_(_1), _1_(_1)), nest1(plus)(_0_(_1), 3)) /*< By the definition, `nest1` has the same semantics as __EGG_LAZY__. >*/
        (i9) == minus(9, plus(9,3))  );

    int w = 7;
    // \x -> (\y -> (\z -> second(y,w,z,x))))
    BOOST_CHECK(
        boost::addressof(
            nest3(second)(_1_(_1), ref3(w), _2_(_1), _0_(_1)) /*< Captures `w` by-reference. >*/
                (i1)(i1)(i1)
        ) == boost::addressof(w) );
}
//]
