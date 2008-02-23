

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/free.hpp>


#include "./egg_example.hpp"


// See also 17.4.4.4.

//[code_example_free
struct cage
{
    int prisoner;
};

result_of_free<int (cage::*)>::type const
    freed_prisoner = BOOST_EGG_FREE(&cage::prisoner);

void egg_example()
{
    cage c = {777};
    BOOST_CHECK(freed_prisoner(c) == 777);
}
//]
