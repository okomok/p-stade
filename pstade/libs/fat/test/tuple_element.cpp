#include <pstade/vodka/drink.hpp>


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_get
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/fat/tuple_element.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/fat/is_same.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(PSTADE_FAT_SUPPORTS_FUSION_SEQUENCE)
#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#endif


namespace fat = pstade::fat;
using namespace fat;


typedef std::pair<int, char> pair_t;

BOOST_MPL_ASSERT((boost::is_same<int, tuple_element_c<0, pair_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, tuple_element_c<1, pair_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int, tuple_element_c<0, pair_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, tuple_element_c<1, pair_t const>::type>));


typedef boost::tuples::tuple<int&, double> tup_t;

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_element_c<0, tup_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_element_c<1, tup_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_element_c<0, tup_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_element_c<1, tup_t const>::type>));


#if defined(PSTADE_FAT_SUPPORTS_FUSION_SEQUENCE)

typedef boost::fusion::vector<int&, double> seq_t;

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_element_c<0, seq_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_element_c<1, seq_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_element_c<0, seq_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_element_c<1, seq_t const>::type>));

#endif


void pstade_minimal_test()
{
}
