

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/bind_left1.hpp>
#include <boost/egg/detail/bind_leftx.hpp>
#include "./egg_test.hpp"


#include <boost/egg/result_of.hpp>
#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"


#if 0 // rejected
typedef int arr_t[20];
BOOST_MPL_ASSERT((boost::is_same<detail::bound<arr_t const>::type, int const(&)[20]>));
PSTADE_TEST_IS_SAME((detail::bound<int const>::type), (int))
#endif 


void egg_test()
{
}
