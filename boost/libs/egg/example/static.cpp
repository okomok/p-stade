

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/static.hpp>
#include <boost/egg/apply.hpp>
#include <boost/mpl/always.hpp>
#include <functional> // plus
#include <cstddef> // ptrdiff_t


#include "./egg_example.hpp"


//[code_example_static
typedef static_<X_apply<boost::mpl::_1>, by_value>::type T_apply_by_value;
T_apply_by_value const apply_by_value = BOOST_EGG_STATIC();

typedef static_< boost::mpl::always< std::plus<int> > >::type T_my_plus; /*< `T_my_plus` is __POD__, whereas `std::plus<int>` is not. >*/
T_my_plus const my_plus = BOOST_EGG_STATIC();

std::ptrdiff_t distance(int *first, int *last) { return last - first; }

void egg_example()
{
    int a[2] = {1,2};
    BOOST_CHECK( apply_by_value(distance, a, a+2) == 2 ); /*< `distance` and `a` are decayed. >*/
    BOOST_CHECK( my_plus(a[0], a[1]) == 3 );
}
//]
