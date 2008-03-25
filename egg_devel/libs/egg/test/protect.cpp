

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/protect.hpp>
#include <boost/egg/bind.hpp>
#include <boost/egg/placeholders.hpp>
#include "./egg_test.hpp"


namespace egg = boost::egg;


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
    using egg::bind;
    using egg::protect;
    using namespace egg::placeholders;

    int ignored = 0;

    int _10 = 10;
    int _20 = 20;
    int _30 = 30;

    BOOST_CHECK( _1 (_10) == 10 );
    BOOST_CHECK( _1 (_10, ignored) == 10 );
    BOOST_CHECK( _1 (_10, ignored, ignored) == 10 );

    BOOST_CHECK( protect(_1)(ignored) (_20) == 20 );
    BOOST_CHECK( protect(_1)(ignored) (_30, ignored, ignored) == 30 );


    // \x -> (\y -> foo(x, y, 30))
    BOOST_CHECK( 10+20*30 ==
        bind(bind, foo, _1, protect(_1), 30) (_10)(_20)
    );
    /*
        bind(bind, foo, _1, protect(_1), 30) (_10)(_20);
        = bind(_apply(foo, _10), _apply(_1, _10), _apply(protect(_1), _10), _apply(30, _10)) (_20);
        = bind(foo, _1(_10), protect(_1)(_10), 30) (_20);
        = bind(foo, _10, _1, 30) (_20);
        = foo(_apply(_10, _20), _apply(_1, _20), _apply(30, _20));
        = foo(_10, _1(_20), 30);
        = foo(_10, _20, 30);
    */

    // \x -> (\y,z -> foo(x, y, z))
    BOOST_CHECK( 10+20*30 ==
        bind(bind, foo, _1, protect(_1), protect(_2))
            (_10)(_20, _30)
    );

    // \x -> (\y -> (\z -> foo(x, y, z)))
    BOOST_CHECK( 10+20*30 ==
        bind(bind, bind, foo, _1, protect(_1), protect(protect(_1)))
            (_10)(_20)(_30)
    );
}
