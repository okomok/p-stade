#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/inlined.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/const.hpp>


int square(int n)
{
    return n * n;
}

typedef pstade::egg::inlined<int(*)(int), &square>::type T_insquare;
PSTADE_EGG_CONST((T_insquare), insquare) = PSTADE_EGG_INLINED();

typedef pstade::egg::inlined<int(*)(int), square>::type T_insquare_;
PSTADE_EGG_CONST((T_insquare_), insquare_) = PSTADE_EGG_INLINED();

#if 0 // gcc-4.1 doesn't work.
typedef pstade::egg::inlined<int(&)(int), square>::type T_rinsquare;
PSTADE_EGG_CONST((T_rinsquare), rinsquare) = PSTADE_EGG_INLINED();
#endif

template<class Ptr, Ptr ptr>
void test_tpl()
{
    BOOST_CHECK(( typename pstade::egg::inlined<Ptr, ptr>::type()(3) == 9 ));

#if 0 // Only msvc-9.0 works.
    BOOST_CHECK( PSTADE_EGG_INLINE(ptr)(3) == 9 );
    BOOST_CHECK( PSTADE_EGG_INLINE_BY(ptr, pstade::egg::by_value)(3) == 9 );
#endif
}

void pstade_minimal_test()
{
    {
        BOOST_CHECK( insquare(3) == 9 );
        BOOST_CHECK( insquare_(3) == 9 );

   //     BOOST_CHECK( inline_(&square).of<&square>()(3) == 9 );

        BOOST_CHECK( PSTADE_EGG_INLINE(&square)(3) == 9 );
        BOOST_CHECK( PSTADE_EGG_INLINE_BY(&square, pstade::egg::by_value)(3) == 9 );

        BOOST_CHECK( PSTADE_EGG_INLINE(square)(3) == 9 );
        BOOST_CHECK( PSTADE_EGG_INLINE_BY(square, pstade::egg::by_value)(3) == 9 );

        BOOST_CHECK( PSTADE_EGG_INLINE(::square)(3) == 9 );
        BOOST_CHECK( PSTADE_EGG_INLINE_BY(::square, pstade::egg::by_value)(3) == 9 );

#if 0 // gcc-4.1 doesn't work.
        BOOST_CHECK( rinsquare(3) == 9 );
#endif
    }

    ::test_tpl<int(*)(int), &square>();
}
