#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/flip.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


int minus(int a, int b)
{
    return a - b;
}


struct less
{
    typedef bool result_type;

    bool operator()(int i, int j) const
    {
        return i < j;
    }
};


void pstade_minimal_test()
{
    {
        BOOST_CHECK(flip(&minus)(0, 1) == 1);
        BOOST_CHECK(flip(&minus)(1, 0) == -1);
    }
    {
        ::less l;
        result_of_flip< ::less >::type fl = PSTADE_EGG_FLIP_L l PSTADE_EGG_FLIP_R;
        BOOST_CHECK( l(0, 1) );
        BOOST_CHECK( !fl(0, 1) );
    }
}
