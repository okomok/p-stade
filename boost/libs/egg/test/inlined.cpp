

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/inlined.hpp>
#include "./egg_test.hpp"


#include <boost/egg/const.hpp>


int square(int n)
{
    return n * n;
}

typedef pstade::egg::inlined<int(*)(int), &square>::type T_insquare;
BOOST_EGG_CONST((T_insquare), insquare) = BOOST_EGG_INLINED();

typedef pstade::egg::inlined<int(*)(int), square>::type T_insquare_;
BOOST_EGG_CONST((T_insquare_), insquare_) = BOOST_EGG_INLINED();

#if 0 // gcc-4.1 doesn't work.
typedef pstade::egg::inlined<int(&)(int), square>::type T_rinsquare;
BOOST_EGG_CONST((T_rinsquare), rinsquare) = BOOST_EGG_INLINED();
#endif

template<class Ptr, Ptr ptr>
void test_tpl()
{
    BOOST_CHECK(( typename pstade::egg::inlined<Ptr, ptr>::type()(3) == 9 ));

#if 0 // Only msvc-9.0 works.
    BOOST_CHECK( BOOST_EGG_INLINE(ptr)(3) == 9 );
#endif
}

void egg_test()
{
    {
        BOOST_CHECK( insquare(3) == 9 );
        BOOST_CHECK( insquare_(3) == 9 );

   //     BOOST_CHECK( inline_(&square).of<&square>()(3) == 9 );

        BOOST_CHECK( BOOST_EGG_INLINE(&square)(3) == 9 );

        BOOST_CHECK( BOOST_EGG_INLINE(square)(3) == 9 );

        BOOST_CHECK( BOOST_EGG_INLINE(::square)(3) == 9 );

#if 0 // gcc-4.1 doesn't work.
        BOOST_CHECK( rinsquare(3) == 9 );
#endif
    }

    ::test_tpl<int(*)(int), &square>();
}
