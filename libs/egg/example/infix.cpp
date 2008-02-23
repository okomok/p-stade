

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/infix.hpp>
#include <functional> // plus


#include "./egg_example.hpp"


//[code_example_infix
void egg_example()
{
    using namespace infix;

    std::plus<int> plus;
    BOOST_CHECK( (1 ^plus^ 2) == 3 );
}
//]
