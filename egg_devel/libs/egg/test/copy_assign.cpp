

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/copy_assign.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


struct A { A() { } template<class X> explicit A(X) { } };
struct B { operator A() const { return A(); } };


void egg_test()
{
    {
        int i = 0;
        BOOST_CHECK( copy_assign(i, 3) == 3 );
        BOOST_CHECK( (i|copy_assign(4)) == 4 );
        BOOST_CHECK( i == 4 );
    }
    {// copy-initialization with no ambiguity.
        A a; B b;
        copy_assign(a, b);
    }
}
