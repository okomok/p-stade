

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/return.hpp>
#include <string>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_return
void egg_example()
{
    BOOST_CHECK( egg::return_<std::string>(bll::_1)("string").size() == 6 );
}
//]
