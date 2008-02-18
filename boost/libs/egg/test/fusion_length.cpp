

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy get
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/fusion/length.hpp>
#include "./egg_test.hpp"


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(BOOST_EGG_HAS_FUSIONS)
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#endif


using namespace pstade::egg;


typedef std::pair<int, char> pair_t;

BOOST_MPL_ASSERT((boost::mpl::equal_to< fusion_length<pair_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< fusion_length<pair_t const>, boost::mpl::int_<2> >));


typedef boost::tuples::tuple<int&, double> tup_t;

BOOST_MPL_ASSERT((boost::mpl::equal_to< fusion_length<tup_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< fusion_length<tup_t const>, boost::mpl::int_<2> >));


#if defined(BOOST_EGG_HAS_FUSIONS)

typedef boost::fusion::vector<int&, double> seq_t;

BOOST_MPL_ASSERT((boost::mpl::equal_to< fusion_length<seq_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< fusion_length<seq_t const>, boost::mpl::int_<2> >));

#endif


void egg_test()
{
    pair_t p(1, 'a');

    tup_t t(p.first, 1.0);

#if defined(BOOST_EGG_HAS_FUSIONS)
    seq_t s(p.first, 1.0);
    BOOST_CHECK( fusion_length<seq_t>::value == 2);
#endif

    BOOST_CHECK( fusion_length<pair_t>::value == 2);
    BOOST_CHECK( fusion_length<tup_t>::value == 2);
    BOOST_CHECK( fusion_length<boost::tuples::null_type>::value == 0 );
}
