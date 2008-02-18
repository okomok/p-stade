

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy get
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/get.hpp>
#include "./egg_test.hpp"


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/egg/is_same.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>

#if defined(BOOST_EGG_HAS_FUSIONS)
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#endif


#include "./using_egg.hpp"


typedef std::pair<int, char> pair_t;

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get_c<0>(pair_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char&, pstade::result_of<X_get_c<1>(pair_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int const&, pstade::result_of<X_get_c<0>(pair_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, pstade::result_of<X_get_c<1>(pair_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int const&, pstade::result_of<X_get_c<0>(pair_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, pstade::result_of<X_get_c<1>(pair_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int const&, pstade::result_of<X_get_c<0>(pair_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, pstade::result_of<X_get_c<1>(pair_t const)>::type>));


typedef boost::tuples::tuple<int&, double> tup_t;

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get<boost::mpl::int_<0> >(tup_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double&, pstade::result_of<X_get<boost::mpl::int_<1> >(tup_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get<boost::mpl::int_<0> >(tup_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, pstade::result_of<X_get<boost::mpl::int_<1> >(tup_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get<boost::mpl::int_<0> >(tup_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, pstade::result_of<X_get<boost::mpl::int_<1> >(tup_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get<boost::mpl::int_<0> >(tup_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, pstade::result_of<X_get< boost::mpl::int_<1> >(tup_t const)>::type>));


#if defined(BOOST_EGG_HAS_FUSIONS)

typedef boost::fusion::vector<int&, double> seq_t;

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get<boost::mpl::int_<0> >(seq_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double&, pstade::result_of<X_get<boost::mpl::int_<1> >(seq_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get<boost::mpl::int_<0> >(seq_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, pstade::result_of<X_get<boost::mpl::int_<1> >(seq_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get<boost::mpl::int_<0> >(seq_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, pstade::result_of<X_get<boost::mpl::int_<1> >(seq_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, pstade::result_of<X_get<boost::mpl::int_<0> >(seq_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, pstade::result_of<X_get< boost::mpl::int_<1> >(seq_t const)>::type>));

#endif



void egg_test()
{
    pair_t p(1, 'a');
    BOOST_CHECK( egg::is_same(p.first, egg::get_c<0>(p)) );
    BOOST_CHECK( egg::is_same(p.second, egg::get_c<1>(p)) );

    tup_t t(p.first, 1.0);
    BOOST_CHECK( egg::is_same(boost::get<0>(t), egg::get<boost::mpl::int_<0> >(t)) );
    BOOST_CHECK( egg::is_same(boost::get<1>(t), egg::get<boost::mpl::int_<1> >(t)) );

    BOOST_CHECK( egg::is_same(boost::get<0>(t), egg::get_c<0>(t)) );
    BOOST_CHECK( egg::is_same(boost::get<1>(t), egg::get_c<1>(t)) );

#if defined(BOOST_EGG_HAS_FUSIONS)
    seq_t s(p.first, 1.0);
    BOOST_CHECK( egg::is_same(boost::fusion::at_c<0>(s), egg::get<boost::mpl::int_<0> >(s)) );
    BOOST_CHECK( egg::is_same(boost::fusion::at_c<1>(s), egg::get<boost::mpl::int_<1> >(s)) );

    BOOST_CHECK( egg::is_same(boost::fusion::at_c<0>(s), egg::get_c<0>(s)) );
    BOOST_CHECK( egg::is_same(boost::fusion::at_c<1>(s), egg::get_c<1>(s)) );
#endif
}
