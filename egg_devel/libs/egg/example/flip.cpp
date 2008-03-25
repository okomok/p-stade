

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/flip.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_flip
void egg_example()
{
    BOOST_CHECK( flip(bll::_1 - bll::_2)(3, 8) == 5 );
}
//]
