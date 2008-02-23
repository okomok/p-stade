

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/array.hpp>
#include "./egg_test.hpp"


void egg_test()
{
    // gcc-4.1 warning: missing braces around initializer for 'int [4]'
    boost::array<int, 4> a = { 1,2,3,4 };
    (void)a;
}
