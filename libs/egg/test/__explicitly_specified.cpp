

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./egg_test.hpp"


#include <boost/egg/detail/boost_workaround.hpp>


struct T_foo
{
    template< class Re, class A0 >
    Re call(A0& a0) const
    {
        return Re();
    }

    template< class Re, class A0 >
    Re call(A0 const&) const
    {
        return Re();
    }
};


void egg_test()
{
    double const d = 0;
#if !BOOST_WORKAROUND(__GNUC__, == 3)
    T_foo().call<int>(d);
#endif
    (void)d;
}
