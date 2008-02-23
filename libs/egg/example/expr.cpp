

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/expr.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/unfuse.hpp>
#include <boost/typeof/typeof.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_expr
void egg_example()
{
    BOOST_AUTO(f,
        egg::expr<int(int, int)>(unfuse(fuse(bll::_1 + bll::_2))) );

    BOOST_CHECK( f(1,2) == 1+2 );
}
//]

