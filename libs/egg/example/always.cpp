

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/always.hpp>
#include <string>


#include "./egg_example.hpp"


//[code_example_always
void egg_example()
{
    int ten = 10;
    BOOST_CHECK( always(ten)(1,2,3,4,5) == 10 );
    BOOST_CHECK( &(always_ref(ten)(1,2,3,4,5)) == &ten );
}
//]
