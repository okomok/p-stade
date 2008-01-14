#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/strong_assign.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct A { A() { } template<class X> explicit A(X) { } };
struct B { operator A() const { return A(); } };


void pstade_minimal_test()
{
    {
        int i = 0;
        BOOST_CHECK( strong_assign(i, 3) == 3 );
        BOOST_CHECK( (i|strong_assign(4)) == 4 );
        BOOST_CHECK( i == 4 );
    }

    {// copy-initialization with no ambiguity.
        A a; B b;
        strong_assign(a, b);
    }
}
