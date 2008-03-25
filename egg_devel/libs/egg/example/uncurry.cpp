

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/uncurry.hpp>
#include <boost/egg/curry.hpp>
#include <functional> // plus


#include "./egg_example.hpp"


//[code_example_uncurry
void egg_example()
{
    std::plus<int> std_plus;
    BOOST_CHECK( uncurry(curry2(std_plus))(4, 9) == 13 );
}
//]
