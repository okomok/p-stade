#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/return_of.hpp>
#include <pstade/lightweight_test.hpp>


#include <pstade/egg/plus.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


using pstade::egg::T_plus;
using pstade::return_of;
using boost::is_same;


BOOST_MPL_ASSERT((is_same<return_of<T_plus(int, int)>::type, int>));
BOOST_MPL_ASSERT((is_same<return_of<T_plus(return_of<T_plus(int, int)>, int)>::type, int>));
BOOST_MPL_ASSERT((is_same<return_of<T_plus(int, return_of<T_plus(int, int)>)>::type, int>));
BOOST_MPL_ASSERT((is_same<return_of<T_plus(return_of<T_plus(int, int)>, return_of<T_plus(int, int)>)>::type, int>));
BOOST_MPL_ASSERT((is_same<return_of<T_plus(return_of<T_plus(int, return_of<T_plus(int, int)>)>, int)>::type, int>));
BOOST_MPL_ASSERT((is_same<return_of<T_plus(int, return_of<T_plus(int, return_of<T_plus(int, int)>)>)>::type, int>));
BOOST_MPL_ASSERT((is_same<return_of<T_plus(return_of<T_plus(int, return_of<T_plus(int, return_of<T_plus(int, int)>)>)>, int)>::type, int>));


void pstade_lightweight_test()
{
}
