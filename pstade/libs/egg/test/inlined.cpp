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


namespace egg = pstade::egg;
using namespace egg;


int square(int n)
{
    return n * n;
}

typedef inlined<int(*)(int), &square>::type T_insquare;
PSTADE_EGG_CONST((T_insquare), insquare) = PSTADE_EGG_INLINED();

#if 0
typedef inlined<int(&)(int), square>::type T_rinsquare;
PSTADE_EGG_CONST((T_rinsquare), rinsquare) = PSTADE_EGG_INLINED();
#endif

void pstade_minimal_test()
{
    {
        BOOST_CHECK( insquare(3) == 9 );
   //     BOOST_CHECK( inline_(&square).of<&square>()(3) == 9 );
        BOOST_CHECK( PSTADE_EGG_INLINE(&square)(3) == 9 );
        BOOST_CHECK( PSTADE_EGG_INLINE_BY(&square, by_value)(3) == 9 );
#if 0
        BOOST_CHECK( rinsquare(3) == 9 );
#endif
    }
}
