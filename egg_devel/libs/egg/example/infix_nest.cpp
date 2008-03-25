

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

    X_nest2<T_bind> nest2;
    XX_0_<T_protect> _0_;
    XX_1_<T_protect> _1_;

    // \x -> (\y -> y - x)
    BOOST_CHECK( (_1_(_1) ^nest2(minus)^ _0_(_1))(5)(8) == 8 - 5 );
}
//]

#else

void egg_example()
{ }

#endif
