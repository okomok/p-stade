

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/flip.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


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


void egg_test()
{
    {
        BOOST_CHECK(flip(&minus)(0, 1) == 1);
        BOOST_CHECK(flip(&minus)(1, 0) == -1);
    }
    {
        ::less l;
        result_of_flip< ::less >::type fl = BOOST_EGG_FLIP(l);
        BOOST_CHECK( l(0, 1) );
        BOOST_CHECK( !fl(0, 1) );
    }
}
