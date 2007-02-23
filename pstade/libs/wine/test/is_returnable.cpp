#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/is_returnable.hpp>


#include <boost/mpl/assert.hpp>


using pstade::is_returnable;


struct base { };
struct derived : base { };


BOOST_MPL_ASSERT_NOT(( is_returnable<int, int&> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<int, int const&> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<int, int*> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<int, int const*> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<int&, const double&> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<int*, const double*> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<base, derived> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<derived, base&> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<derived, base const&> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<derived, base*> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<derived, base const*> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<derived const&, base&> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<derived const*, base*> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<derived*&, base*&> ));
BOOST_MPL_ASSERT_NOT(( is_returnable<derived**, base**> ));


BOOST_MPL_ASSERT(( is_returnable<int, int> ));
BOOST_MPL_ASSERT(( is_returnable<int, int const> ));
BOOST_MPL_ASSERT(( is_returnable<double, int> ));
BOOST_MPL_ASSERT(( is_returnable<base, base> ));
BOOST_MPL_ASSERT(( is_returnable<derived, base> ));
BOOST_MPL_ASSERT(( is_returnable<derived&, base> ));
BOOST_MPL_ASSERT(( is_returnable<derived&, base&> ));
BOOST_MPL_ASSERT(( is_returnable<derived&, base const&> ));
BOOST_MPL_ASSERT(( is_returnable<derived*, base*> ));
BOOST_MPL_ASSERT(( is_returnable<derived*&, base*> ));
BOOST_MPL_ASSERT(( is_returnable<derived*, base const*> ));
BOOST_MPL_ASSERT(( is_returnable<derived*&, derived*&> ));
BOOST_MPL_ASSERT(( is_returnable<derived*&, derived*> ));


void test()
{
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
