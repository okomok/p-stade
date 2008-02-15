#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/detail/bound.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/utility/addressof.hpp>
#include <pstade/egg/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>


namespace egg = pstade::egg;
using namespace egg;
using pstade::result_of;


BOOST_MPL_ASSERT((boost::is_same<detail::result_of_bound<int const>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<detail::result_of_bound<int const [3]>::type, int const (*)[3]>));

BOOST_MPL_ASSERT((boost::is_same<detail::result_of_unbound<int const>::type, int const &>));
BOOST_MPL_ASSERT((boost::is_same<detail::result_of_unbound<int const (* const)[4]>::type, int const (&)[4]>));


void pstade_minimal_test()
{
    {
        int const a = 999;
        detail::result_of_bound<int const>::type b = detail::bound(a);
        BOOST_CHECK(!is_same(detail::unbound(b), a) );
    }
    {
        int a[3] = {1,2,3};
        detail::result_of_bound<int const [3]>::type b = detail::bound(a);
        BOOST_CHECK( is_same(detail::unbound(b)[1], a[1]) );
    }
}
