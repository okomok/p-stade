#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_get
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/tuple/size.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(PSTADE_EGG_TUPLE_SUPPORTS_FUSION)
#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#endif


namespace egg = pstade::egg;
using namespace egg;


typedef std::pair<int, char> pair_t;

BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<pair_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<pair_t> const, boost::mpl::int_<2> >));


typedef boost::tuples::tuple<int&, double> tup_t;

BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<tup_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<tup_t> const, boost::mpl::int_<2> >));


#if defined(PSTADE_EGG_TUPLE_SUPPORTS_FUSION)

typedef boost::fusion::vector<int&, double> seq_t;

BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<seq_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<seq_t> const, boost::mpl::int_<2> >));

#endif


void pstade_minimal_test()
{
    pair_t p(1, 'a');

    tup_t t(p.first, 1.0);

#if defined(PSTADE_EGG_TUPLE_SUPPORTS_FUSION)
    seq_t s(p.first, 1.0);
    BOOST_CHECK( tuple_size<seq_t>::value == 2);
#endif

    BOOST_CHECK( egg::tuple_size<pair_t>::value == 2);
    BOOST_CHECK( egg::tuple_size<tup_t>::value == 2);
    BOOST_CHECK( egg::tuple_size<boost::tuples::null_type>::value == 0 );
}
