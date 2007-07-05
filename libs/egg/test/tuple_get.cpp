#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_get
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/tuple_get.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(PSTADE_EGG_SUPPORTS_FUSION_SEQUENCE)
#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#endif


namespace egg = pstade::egg;
using namespace egg;


typedef std::pair<int, char> pair_t;

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get_c<0>(pair_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char&, boost::result_of<xp_tuple_get_c<1>(pair_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<xp_tuple_get_c<0>(pair_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<xp_tuple_get_c<1>(pair_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<xp_tuple_get_c<0>(pair_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<xp_tuple_get_c<1>(pair_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<xp_tuple_get_c<0>(pair_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<xp_tuple_get_c<1>(pair_t const)>::type>));


typedef boost::tuples::tuple<int&, double> tup_t;

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get<boost::mpl::int_<0> >(tup_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double&, boost::result_of<xp_tuple_get<boost::mpl::int_<1> >(tup_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get<boost::mpl::int_<0> >(tup_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<xp_tuple_get<boost::mpl::int_<1> >(tup_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get<boost::mpl::int_<0> >(tup_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<xp_tuple_get<boost::mpl::int_<1> >(tup_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get<boost::mpl::int_<0> >(tup_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<xp_tuple_get< boost::mpl::int_<1> >(tup_t const)>::type>));


#if defined(PSTADE_EGG_SUPPORTS_FUSION_SEQUENCE)

typedef boost::fusion::vector<int&, double> seq_t;

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get<boost::mpl::int_<0> >(seq_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double&, boost::result_of<xp_tuple_get<boost::mpl::int_<1> >(seq_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get<boost::mpl::int_<0> >(seq_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<xp_tuple_get<boost::mpl::int_<1> >(seq_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get<boost::mpl::int_<0> >(seq_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<xp_tuple_get<boost::mpl::int_<1> >(seq_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<xp_tuple_get<boost::mpl::int_<0> >(seq_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<xp_tuple_get< boost::mpl::int_<1> >(seq_t const)>::type>));

#endif



void pstade_minimal_test()
{
    pair_t p(1, 'a');
    BOOST_CHECK( egg::is_same(p.first, egg::tuple_get_c<0>(p)) );
    BOOST_CHECK( egg::is_same(p.second, egg::tuple_get_c<1>(p)) );

    tup_t t(p.first, 1.0);
    BOOST_CHECK( egg::is_same(boost::get<0>(t), egg::tuple_get<boost::mpl::int_<0> >(t)) );
    BOOST_CHECK( egg::is_same(boost::get<1>(t), egg::tuple_get<boost::mpl::int_<1> >(t)) );

    BOOST_CHECK( egg::is_same(boost::get<0>(t), egg::tuple_get_c<0>(t)) );
    BOOST_CHECK( egg::is_same(boost::get<1>(t), egg::tuple_get_c<1>(t)) );

#if defined(PSTADE_EGG_SUPPORTS_FUSION_SEQUENCE)
    seq_t s(p.first, 1.0);
    BOOST_CHECK( egg::is_same(boost::fusion::at_c<0>(s), egg::tuple_get<boost::mpl::int_<0> >(s)) );
    BOOST_CHECK( egg::is_same(boost::fusion::at_c<1>(s), egg::tuple_get<boost::mpl::int_<1> >(s)) );

    BOOST_CHECK( egg::is_same(boost::fusion::at_c<0>(s), egg::tuple_get_c<0>(s)) );
    BOOST_CHECK( egg::is_same(boost::fusion::at_c<1>(s), egg::tuple_get_c<1>(s)) );
#endif
}
