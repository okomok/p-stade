#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/reference_is_convertible.hpp>


#include <boost/mpl/assert.hpp>


namespace oven = pstade::oven;
using namespace oven;


BOOST_MPL_ASSERT((detail::reference_is_convertible_aux<int&, int&>));
BOOST_MPL_ASSERT((detail::reference_is_convertible_aux<int, int>));
BOOST_MPL_ASSERT((detail::reference_is_convertible_aux<int&, int>));
BOOST_MPL_ASSERT_NOT((detail::reference_is_convertible_aux<int, int const&>));


void test()
{
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
