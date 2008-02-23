

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/fuse.hpp>
#include <boost/tuple/tuple.hpp>


#include "./egg_example.hpp"


//[code_example_fuse
int unfused_plus(int i, int j, int k)
{
    return i + j + k;
}

void egg_example()
{
    BOOST_CHECK( 1+2+3 == fuse(&unfused_plus)(boost::make_tuple(1,2,3)) );
}
//]
