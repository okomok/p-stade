#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/return.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/egg/plus.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_const.hpp>


namespace egg = pstade::egg;
using namespace egg;

BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_plus(int, int)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_plus(double, double)>::type, double>));


typedef result_of_return_<T_plus, boost::add_const<boost::mpl::_1> >::type T_my_plus2;
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus2(int, int)>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus2(double, double)>::type, double const>));

typedef result_of_return_<T_identity, boost::remove_reference<boost::mpl::_1> >::type T_my_identity;
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_identity(int&)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_identity(double)>::type, double const>));


void pstade_minimal_test()
{
    {
        int x = egg::return_<boost::add_const<boost::mpl::_1> >(plus)(1, 2);
        BOOST_CHECK(x == 3);
    }
    {
        int x = egg::return_<boost::remove_reference<boost::mpl::_1> >(identity)(10);
        BOOST_CHECK(x == 10);
    }
    {
        int a = 10;
        int const &x = egg::return_<boost::mpl::_1>(identity)(a);
        BOOST_CHECK(x == 10);
        BOOST_CHECK(&x == &a);
    }
}
