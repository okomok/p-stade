#include <pstade/vodka/drink.hpp>


// PStade.p_stade;
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/oven/metafunctions.hpp>

BOOST_MPL_ASSERT_NOT((boost::is_same<int, ptrdiff_t>));
BOOST_MPL_ASSERT((boost::is_same< pstade::oven::range_difference<int [10]>::type, int> ));


int main()
{
}
