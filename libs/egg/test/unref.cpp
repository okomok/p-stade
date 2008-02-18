#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/unref.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


namespace egg = pstade::egg;
using namespace egg;

BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_perfect, int&>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_perfect, int const&>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_perfect, int>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_perfect, int const>::type, int const>));


BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_ref, int&>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_ref, int const&>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_ref, int const>::type, int const>));


BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_cref, int&>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_cref, int const&>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_cref, int>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_cref, int const>::type, int const>));


BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int&>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int const&>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int const>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int (&)(int)>::type, int (*)(int)>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int [12]>::type, int *>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int const [12]>::type, int const*>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int (&)[12]>::type, int *>));
BOOST_MPL_ASSERT((boost::is_same<detail::unref<by_value, int const (&)[12]>::type, int const*>));


void pstade_minimal_test()
{
}
