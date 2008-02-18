

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy get
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/fusion/prepend.hpp>
#include "./egg_test.hpp"


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>
#include <boost/egg/get.hpp>

#include <boost/egg/by_ref.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_value.hpp>

#if defined(BOOST_EGG_HAS_FUSIONS)
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#endif


#include "./using_egg.hpp"

typedef boost::tuples::tuple<int&, double> tup_t;

#if !defined(BOOST_EGG_HAS_FUSIONS)
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int&, tup_t>, pstade::result_of<X_fusion_prepend<by_perfect>(tup_t&, int&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int const&, tup_t>, pstade::result_of<X_fusion_prepend<by_perfect>(tup_t&, int const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int const&, tup_t>, pstade::result_of<X_fusion_prepend<by_perfect>(tup_t&, int)>::type>));

BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int&, tup_t>, pstade::result_of<X_fusion_prepend<by_ref>(tup_t&, int&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int const&, tup_t>, pstade::result_of<X_fusion_prepend<by_ref>(tup_t&, int const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int const&, tup_t>, pstade::result_of<X_fusion_prepend<by_ref>(tup_t&, int const)>::type>));

BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int const&, tup_t>, pstade::result_of<X_fusion_prepend<by_cref>(tup_t&, int&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int const&, tup_t>, pstade::result_of<X_fusion_prepend<by_cref>(tup_t&, int const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int const&, tup_t>, pstade::result_of<X_fusion_prepend<by_cref>(tup_t&, int)>::type>));

BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int, tup_t>, pstade::result_of<X_fusion_prepend<by_value>(tup_t&, int&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int, tup_t>, pstade::result_of<X_fusion_prepend<by_value>(tup_t&, int const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<boost::tuples::cons<int, tup_t>, pstade::result_of<X_fusion_prepend<by_value>(tup_t&, int)>::type>));
#endif

void egg_test()
{
    {
        int i = 10;
        tup_t t(i, 1.0);

        int v = 999;
        BOOST_CHECK( egg::is_same(v, egg::get_c<0>(fusion_prepend(t, v))) );
        BOOST_CHECK( !egg::is_same(v, egg::get_c<0>(X_fusion_prepend<by_value>()(t, v))) ); // copied
        BOOST_CHECK( egg::is_same(boost::get<0>(t), egg::get_c<1>(fusion_prepend(t, v))) );
        BOOST_CHECK( !egg::is_same(boost::get<1>(t), egg::get_c<2>(fusion_prepend(t, v))) ); // copied without Fusion.
    }

#if defined(BOOST_EGG_HAS_FUSIONS)
    {
        int i = 10;
        boost::fusion::vector<int&, double> t(i, 1.0);

        int v = 999;
        BOOST_CHECK( egg::is_same(v, egg::get_c<0>(fusion_prepend(t, v))) );
        BOOST_CHECK( !egg::is_same(v, egg::get_c<0>(X_fusion_prepend<by_value>()(t, v))) ); // copied
        BOOST_CHECK( egg::is_same(boost::fusion::at_c<0>(t), egg::get_c<1>(fusion_prepend(t, v))) );
        BOOST_CHECK( egg::is_same(boost::fusion::at_c<1>(t), egg::get_c<2>(fusion_prepend(t, v))) ); // not copied with Fusion.
    }
#endif
}
