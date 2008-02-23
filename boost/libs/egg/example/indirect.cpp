

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/indirect.hpp>
#include <boost/egg/pipable.hpp>
#include <boost/tuple/tuple.hpp>
#include <functional> // plus


#include "./egg_example.hpp"


//[code_example_indirect
typedef
    result_of_pipable< /*< Let's `pipable` be __EGG_PIPABLE__.>*/
        result_of_indirect<T_pipable const *>::type
    >::type
T_pipi;

T_pipi const pipi /*< `&pipable` is an /address constant expression/, so that `pipi` can be /statically initialized/. >*/
  = BOOST_EGG_PIPABLE_L
        BOOST_EGG_INDIRECT(&pipable) /*< A macro invocation must be sandwiched using `_L` and `_R`. >*/
    BOOST_EGG_PIPABLE_R;

void egg_example()
{
    std::plus<int> plus;
    BOOST_CHECK( (1|(plus|pipi)(3)) == 1+3 );
}
//]
