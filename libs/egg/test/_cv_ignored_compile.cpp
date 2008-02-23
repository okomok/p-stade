

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./egg_test.hpp"

#include <boost/egg/detail/boost_workaround.hpp>


template<class T>
void foo(T const&) {}

void bar() {}


void egg_test()
{
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    ::foo(bar);
#endif
}
