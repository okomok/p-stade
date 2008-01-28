#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/free.hpp>
#include <pstade/minimal_test.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct my
{
    int plus(int x, int y) const
    {
        return x + y;
    }

    int two() const
    {
        return 2;
    }
};


result_of_free<int(my::*)(int, int) const>::type const
    freed_plus = PSTADE_EGG_FREE(&my::plus);


void pstade_minimal_test()
{
    my y;
    {
        BOOST_CHECK( 12 == freed_plus(y, 5, 7) );
        BOOST_CHECK( 12 == freed_plus(&y, 5, 7) );
    }
    {
        BOOST_CHECK( 12 == free_(&my::plus)(y, 5, 7) );
        BOOST_CHECK( 12 == free_(&my::plus)(&y, 5, 7) );
    }
    {
        BOOST_CHECK( 2 == free_(&my::two)(y) );
        BOOST_CHECK( 2 == free_(&my::two)(&y) );
    }
}
