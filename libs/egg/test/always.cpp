#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/always.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/ref.hpp>


namespace egg = pstade::egg;
using namespace egg;


result_of_always<int>::type const always_3 = PSTADE_EGG_ALWAYS_L 3 PSTADE_EGG_ALWAYS_R;

void pstade_minimal_test()
{
    {
        int i = 3;
        BOOST_CHECK( always(i)() == 3 );
        int & i_ = always(boost::ref(i))(6,7,8);
        BOOST_CHECK( &i_ == &i );
        BOOST_CHECK( always(3)() == 3 );
        BOOST_CHECK( always_3(i) == 3 );
        BOOST_CHECK( always(3)(4, 5) == 3 );
        BOOST_CHECK( always_3(6,7,8,9,1) == 3 );
    }
}