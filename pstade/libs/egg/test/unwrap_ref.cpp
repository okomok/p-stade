#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/unwrap_ref.hpp>
#include <pstade/lightweight_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>


namespace egg = pstade::egg;
using namespace egg;
using pstade::result_of;


BOOST_MPL_ASSERT((boost::is_same<int&, result_of<T_unwrap_ref(int&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, result_of<T_unwrap_ref(int const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, result_of<T_unwrap_ref(int)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, result_of<T_unwrap_ref(int const)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, result_of<T_unwrap_ref(boost::reference_wrapper<int>&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int&, result_of<T_unwrap_ref(boost::reference_wrapper<int> const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int&, result_of<T_unwrap_ref(boost::reference_wrapper<int>)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int&, result_of<T_unwrap_ref(boost::reference_wrapper<int> const)>::type>));


BOOST_MPL_ASSERT((boost::is_same<int const&, result_of<T_unwrap_ref(boost::reference_wrapper<int const>&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, result_of<T_unwrap_ref(boost::reference_wrapper<int const> const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, result_of<T_unwrap_ref(boost::reference_wrapper<int const>)>::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, result_of<T_unwrap_ref(boost::reference_wrapper<int const> const)>::type>));


void pstade_lightweight_test()
{
    {
        int x = 999;
        int& x_ = unwrap_ref(x);
        BOOST_CHECK(&x == &x_);
    }
    {
        int x = 999;
        int& x_ = unwrap_ref(boost::ref(x));
        BOOST_CHECK(&x == &x_);
    }
}
