

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/placeholders.hpp>
#include <boost/egg/result_of.hpp>


#include "./egg_example.hpp"


//[code_example_bll_placeholders
void egg_example()
{
    int ten = 10;
    result_of_<T_bll_1(int &)>::type r = bll_1(ten);
    BOOST_CHECK( r == 10 );
}
//]
