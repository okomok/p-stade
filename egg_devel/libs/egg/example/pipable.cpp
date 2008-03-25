

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pipable.hpp>


#include "./egg_example.hpp"


//[code_example_pipable
struct weird_mult
{
    typedef int result_type;

    int operator()(int x) const
    {
        return x * x;
    }

    int operator()(int x, int y) const
    {
        return x * y;
    }

    int operator()(int x, int y, int z) const
    {
        return x * y * z;
    }
};

result_of_pipable<weird_mult>::type const mult = BOOST_EGG_PIPABLE({});

void egg_example()
{
    BOOST_CHECK( ( 2|mult ) == 2 * 2 );
    BOOST_CHECK( ( 2|mult() ) == 2 * 2 );
    BOOST_CHECK( ( 2|mult(3)|mult(4) ) == 2 * 3 * 4 );
    BOOST_CHECK( ( 2|mult(3, 4) ) == 2 * 3 * 4 );

    BOOST_CHECK( ( mult|=2 ) == 2 * 2 );
    BOOST_CHECK( ( mult()|=2 ) == 2 * 2 );
    BOOST_CHECK( ( mult|=mult|=2) == (2 * 2) * (2 * 2) );

    BOOST_CHECK( ( mult(3)|=2 ) == 2 * 3 );
    BOOST_CHECK( ( mult(3, 4)|= 2 ) == 2 * 3 * 4 );
}
//]
