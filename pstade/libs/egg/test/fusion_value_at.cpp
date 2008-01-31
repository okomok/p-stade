#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy fusion_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/fusion/value_at.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(PSTADE_EGG_HAS_FUSIONS)
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#endif


namespace egg = pstade::egg;
using namespace egg;


typedef std::pair<int, char> pair_t;

BOOST_MPL_ASSERT((boost::is_same<int, fusion_value_at_c<0, pair_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, fusion_value_at_c<1, pair_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int, fusion_value_at_c<0, pair_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, fusion_value_at_c<1, pair_t const>::type>));


typedef boost::tuples::tuple<int&, double> tup_t;

BOOST_MPL_ASSERT((boost::is_same<int&, fusion_value_at_c<0, tup_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, fusion_value_at_c<1, tup_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, fusion_value_at_c<0, tup_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, fusion_value_at_c<1, tup_t const>::type>));


#if defined(PSTADE_EGG_HAS_FUSIONS)

typedef boost::fusion::vector<int&, double> seq_t;

BOOST_MPL_ASSERT((boost::is_same<int&, fusion_value_at_c<0, seq_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, fusion_value_at_c<1, seq_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, fusion_value_at_c<0, seq_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, fusion_value_at_c<1, seq_t const>::type>));

#endif


void pstade_minimal_test()
{
}
