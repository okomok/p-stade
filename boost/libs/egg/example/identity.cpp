

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/identity.hpp>


#include "./egg_example.hpp"


//[code_example_identity
void egg_example()
{
    BOOST_CHECK( identity(10) == 10 );
}
//]
