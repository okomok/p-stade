

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/infix.hpp>
#include <boost/egg/bind.hpp>
#include <boost/egg/protect.hpp>
#include <boost/egg/placeholders.hpp>
#include <boost/egg/functional.hpp> // minus
#include <boost/egg/nest.hpp>
#include <boost/version.hpp>


#include "./egg_example.hpp"


#if BOOST_VERSION >= 103500 // works only if boost::is_placeholder available.

//[code_example_infix_nest
void egg_example()
{
    using namespace infix;
    using namespace placeholders;

    X_nest0<T_bind, T_protect> nest0;
    X_nest1<T_bind, T_protect> nest1;
    X_nest2<T_bind, T_protect> nest2;

    // \x -> (\y -> y - x)
    BOOST_CHECK( (nest1(_1) ^nest2(minus)^ nest0(_1))(5)(8) == 8 - 5 );
}
//]

#else

void egg_example()
{ }

#endif
