#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/is_convertible.hpp>
#include <pstade/lightweight_test.hpp>


#include <boost/mpl/assert.hpp>


using pstade::is_convertible;


BOOST_MPL_ASSERT(( is_convertible<int, int> ));
BOOST_MPL_ASSERT(( is_convertible<int *, int const *> ));

BOOST_MPL_ASSERT_NOT(( is_convertible<int const *, int *> ));


void pstade_lightweight_test()
{ }
