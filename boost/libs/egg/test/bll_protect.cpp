

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/protect.hpp>
#include "./egg_test.hpp"


#include <boost/egg/bll/bind.hpp>
#include <boost/egg/bll/placeholders.hpp>


#include "./using_egg.hpp"


struct T_foo
{
    typedef int result_type;

    int operator()(int i, int j, int k) const
    {
        return i + j * k;
    }
};

T_foo const foo = {};


void egg_test()
{
    using egg::bll_bind;
    using egg::bll_protect;
    using egg::bll_1;
    using egg::bll_2;

    int ignored = 0;

    int _10 = 10;
    int _20 = 20;
    int _30 = 30;

    BOOST_CHECK( bll_1 (_10) == 10 );
    BOOST_CHECK( bll_1 (_10, ignored) == 10 );
    BOOST_CHECK( bll_1 (_10, ignored, ignored) == 10 );

    BOOST_CHECK( bll_protect(bll_1)(ignored) (_20) == 20 );
    BOOST_CHECK( bll_protect(bll_1)(ignored) (_30, ignored, ignored) == 30 );


    // \x -> (\y -> foo(x, y, 30))
    BOOST_CHECK( 10+20*30 ==
        bll_bind(bll_bind, foo, bll_1, bll_protect(bll_1), 30) (_10)(_20)
    );
    /*
        bll_bind(bll_bind, foo, bll_1, bll_protect(bll_1), 30) (_10)(_20);
        = bll_bind(_apply(foo, _10), _apply(bll_1, _10), _apply(bll_protect(bll_1), _10), _apply(30, _10)) (_20);
        = bll_bind(foo, bll_1(_10), bll_protect(bll_1)(_10), 30) (_20);
        = bll_bind(foo, _10, bll_1, 30) (_20);
        = foo(_apply(_10, _20), _apply(bll_1, _20), _apply(30, _20));
        = foo(_10, bll_1(_20), 30);
        = foo(_10, _20, 30);
    */

    // \x -> (\y,z -> foo(x, y, z))
    BOOST_CHECK( 10+20*30 ==
        bll_bind(bll_bind, foo, bll_1, bll_protect(bll_1), bll_protect(bll_2))
            (_10)(_20, _30)
    );

    // \x -> (\y -> (\z -> foo(x, y, z)))
    BOOST_CHECK( 10+20*30 ==
        bll_bind(bll_bind, bll_bind, foo, bll_1, bll_protect(bll_1), bll_protect(bll_protect(bll_1)))
            (_10)(_20)(_30)
    );
}
