

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/throw.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


void egg_test()
{
    {
        try {
            int i = 3;
            throw_(i);
        }
        catch (int j) {
            BOOST_CHECK(j == 3);
        }
    }
}
