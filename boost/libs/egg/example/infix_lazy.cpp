

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/infix.hpp>
#include <boost/egg/bind.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/placeholders.hpp>
#include <boost/egg/functional.hpp> // plus


#include "./egg_example.hpp"


//[code_example_infix_lazy
void egg_example()
{
    using namespace infix;
    using namespace placeholders;

    X_lazy<T_bind> lazy; // T_bll_bind doesn't work, for operator^ is overloaded.

    BOOST_CHECK( (_1 ^lazy(plus)^ _2)(1, 2) == 3 );
}
//]
