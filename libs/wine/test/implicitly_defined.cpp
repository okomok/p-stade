#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/implicitly_defined.hpp>
#include <pstade/minimal_test.hpp>



struct my_derived;


struct my_base
{
    my_base() {}
    my_base(my_base const&) {}
    my_base(my_derived const&) { BOOST_CHECK(false); }

    my_base& operator=(my_base const&) { return *this; }
    my_base& operator=(my_derived const&) { BOOST_CHECK(false); return *this; }
};


struct my_derived : my_base
{
    my_derived() {}

    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(my_derived, my_base)
};


void pstade_minimal_test()
{
    {
        my_derived d1;
        my_derived d2 = d1;
    }
    {
        my_derived d1;
        my_derived d2;
        d2 = d1;
    }
}
