#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/range_constantable.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/oven/iter_range.hpp>


struct my_range :
    pstade::oven::iter_range<int *>,
    pstade::oven::range_constantable< my_range, int const * >
{
    typedef int const *const_iterator; // don't forget this.

    typedef pstade::oven::iter_range<int *> super_t;

    my_range() : super_t((int*)0, (int*)0)
    { }
};


// "primary" must be preferred for non-const type.
template<class X>
void must_be_nonconst_preferred(X&)
{
}

struct A { };

void must_be_nonconst_preferred(A const&)
{
    BOOST_CHECK(false);
}


void must_be_const_ptr(int *)
{
    BOOST_CHECK(false);
}

void must_be_const_ptr(int const *)
{    
}


void must_be_nonconst_ptr(int *)
{
}

void must_be_nonconst_ptr(int const *)
{
    BOOST_CHECK(false);
}


void pstade_minimal_test()
{
    {
        ::A a;
        ::must_be_nonconst_preferred(a);
    }
    {
        ::my_range const rng;
        ::must_be_const_ptr(boost::begin(rng));
    }
    {
        ::my_range rng;
        ::must_be_nonconst_ptr(boost::begin(rng));
    }
}
