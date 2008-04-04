

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/return_of.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/static.hpp>
#include <boost/egg/bind.hpp>
#include <boost/egg/placeholders.hpp>
#include <functional>


#include "./egg_example.hpp"


//[code_example_static_compose
using namespace placeholders;

typedef result_of_lazy<std::plus<int>, T_bind>::type Plus;
typedef result_of_lazy<std::minus<int>, T_bind>::type Minus;

static_<
    return_of< Plus, TT_1, return_of<Minus, TT_2, TT_3> >
>::type const foo = {{}};

void egg_example()
{
    BOOST_CHECK( foo(1,2,3) == 1+(2-3) );
}
//]
