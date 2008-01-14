#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/bll/return_type.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>


namespace bll = boost::lambda;
using namespace bll;

struct A {};

BOOST_MPL_ASSERT((boost::is_same<
                 return_type_2<arithmetic_action<minus_action>, int*, int*>::type,
                 int const
>));

BOOST_MPL_ASSERT((boost::is_same<
                 return_type_1<unary_arithmetic_action<minus_action>, int>::type,
                 int
>));

#if 0
BOOST_MPL_ASSERT((boost::is_same<
                 return_type_2<arithmetic_action<plus_action>, A, A>::type,
                 A
>));
#endif

void pstade_minimal_test()
{

}
