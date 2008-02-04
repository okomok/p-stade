#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_from.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>


struct super
{
    typedef int my_type;
    int foo() { return 1; };
};

struct derived : pstade::derived_from<super>
{ };

BOOST_MPL_ASSERT((boost::is_same<derived::base_class, super>));


void pstade_minimal_test()
{
    derived d;
    d.foo();

    derived::my_type k = 0;
    (void)k;
}
