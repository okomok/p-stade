

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/bind.hpp>
#include <boost/egg/lazy.hpp>
#include <functional> // plus


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_bll_bind
void egg_example()
{
    using bll::_1;
    std::plus<int> plus;
    int _3_ = 3, _4_ = 4;

    // \x -> (\y -> plus(x, y))
    BOOST_CHECK( lazy(bll_bind)(plus, _1, bll::protect(_1)) /*< This is currying in __BOOST_LAMBDA__. >*/
        (_3_)(_4_) == plus(3, 4) );
}
//]
