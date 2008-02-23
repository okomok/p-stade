

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/construct.hpp>
#include <boost/egg/apply.hpp>
#include <string>


#include "./egg_example.hpp"


//[code_example_construct
void egg_example()
{
    BOOST_CHECK( apply(X_construct<int>(), 3) == 3 );
}
//]
