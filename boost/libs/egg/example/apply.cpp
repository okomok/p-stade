

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/apply.hpp>
#include <functional> // negate


#include "./egg_example.hpp"


//[code_example_apply
void egg_example()
{
    std::negate<int> my_negate;
    BOOST_CHECK(
        apply(my_negate, apply(my_negate, apply(my_negate, 10))) == -10 );
}
//]
