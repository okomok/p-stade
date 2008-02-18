#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/detail/bind_left1.hpp>
#include <pstade/egg/detail/bind_leftx.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/result_of.hpp>
#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


#if 0 // rejected
typedef int arr_t[20];
BOOST_MPL_ASSERT((boost::is_same<detail::bound<arr_t const>::type, int const(&)[20]>));
PSTADE_TEST_IS_SAME((detail::bound<int const>::type), (int))
#endif 


void pstade_minimal_test()
{
}
