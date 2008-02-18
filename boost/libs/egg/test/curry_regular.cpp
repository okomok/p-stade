

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/curry.hpp>
#include "./egg_test.hpp"


struct foo
{
    typedef int result_type;

    int operator()(int, int, int) const
    {
        return 0;
    }
};


template<class F>
void regular_check(F f)
{
    F g;
    g = f;
}


void egg_test()
{
    using namespace boost::egg;

    {
        ::regular_check( curry3(foo()) );
        ::regular_check( curry3(foo())(1) );
        ::regular_check( curry3(foo())(1)(2) );
    }
}
