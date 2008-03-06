

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/fix.hpp>
#include <functional> // minus
#include <boost/egg/lazy.hpp>
#include <boost/lambda/if.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_fix
void egg_example()
{
    using bll::_1;
    using bll::_2;

    int r =
        fix2(
            bll::ret<int>(
                // \(f,a) -> a == 0 ? 1 : a * f(a-1)
                bll::if_then_else_return( _2 == 0,
                    1,
                    _2 * lazy(_1)(_2 - 1)
                )
            )
        ) (5);

    BOOST_CHECK(r == 5*4*3*2*1);
}
//]
