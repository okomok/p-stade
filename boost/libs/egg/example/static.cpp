

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/static.hpp>
#include <boost/egg/apply.hpp>


#include "./egg_example.hpp"


//[code_example_static
typedef static_<X_apply<boost::mpl::_1>, by_value>::type T_apply_by_value;
T_apply_by_value const apply_by_value = BOOST_EGG_STATIC();

int increment(int i) { return i + 1; }

void egg_example()
{
    // decayed to function pointer.
    BOOST_CHECK( apply_by_value(increment, 3) == 4 );
}
//]
