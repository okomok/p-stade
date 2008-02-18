

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/inlined.hpp>
#include "./egg_test.hpp"


#include <boost/egg/const.hpp>


struct my {
    int square(int n)
    {
        return n * n;
    }
};

// `&` can't be omitted. See: 5.3.1/3.
typedef pstade::egg::inlined<int(my::*)(int), &my::square>::type T_insquare;
BOOST_EGG_CONST((T_insquare), insquare) = BOOST_EGG_INLINED();

template<class Ptr, Ptr ptr>
void test_tpl(my y)
{
    BOOST_CHECK(( typename pstade::egg::inlined<Ptr, ptr>::type()(y, 3) == 9 ));
    BOOST_CHECK(( typename pstade::egg::inlined<Ptr, ptr>::type()(&y, 3) == 9 ));
}

void egg_test()
{
    my y;
    {
        BOOST_CHECK( insquare(y, 3) == 9 );

        BOOST_CHECK( BOOST_EGG_INLINE(&my::square)(y, 3) == 9 );

        BOOST_CHECK( BOOST_EGG_INLINE(&my::square)(&y, 3) == 9 );
    }

    ::test_tpl<int(my::*)(int), &my::square>(y);
}
