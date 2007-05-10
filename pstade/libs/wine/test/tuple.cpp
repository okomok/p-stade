#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_get
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tuple.hpp>


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/is_same.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(PSTADE_TUPLE_FUSION_SUPPORTED)
#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#endif


using namespace pstade;


typedef std::pair<int, char> pair_t;

BOOST_MPL_ASSERT((boost::is_same<int, tuple_element_c<0, pair_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, tuple_element_c<1, pair_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int, tuple_element_c<0, pair_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, tuple_element_c<1, pair_t const>::type>));

BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<pair_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<pair_t> const, boost::mpl::int_<2> >));


// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get_c<0>(pair_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char&, boost::result_of<op_tuple_get_c<1>(pair_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<op_tuple_get_c<0>(pair_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<op_tuple_get_c<1>(pair_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<op_tuple_get_c<0>(pair_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<op_tuple_get_c<1>(pair_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<op_tuple_get_c<0>(pair_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<op_tuple_get_c<1>(pair_t const)>::type>));


typedef boost::tuples::tuple<int&, double> tup_t;

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_element_c<0, tup_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_element_c<1, tup_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_element_c<0, tup_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_element_c<1, tup_t const>::type>));

BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<tup_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<tup_t> const, boost::mpl::int_<2> >));

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get<boost::mpl::int_<0> >(tup_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double&, boost::result_of<op_tuple_get<boost::mpl::int_<1> >(tup_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get<boost::mpl::int_<0> >(tup_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_get<boost::mpl::int_<1> >(tup_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get<boost::mpl::int_<0> >(tup_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_get<boost::mpl::int_<1> >(tup_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get<boost::mpl::int_<0> >(tup_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_get< boost::mpl::int_<1> >(tup_t const)>::type>));


#if defined(PSTADE_TUPLE_FUSION_SUPPORTED)

typedef boost::fusion::vector<int&, double> seq_t;

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_element_c<0, seq_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_element_c<1, seq_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_element_c<0, seq_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_element_c<1, seq_t const>::type>));

BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<seq_t>, boost::mpl::int_<2> >));
BOOST_MPL_ASSERT((boost::mpl::equal_to< tuple_size<seq_t> const, boost::mpl::int_<2> >));

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get<boost::mpl::int_<0> >(seq_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double&, boost::result_of<op_tuple_get<boost::mpl::int_<1> >(seq_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get<boost::mpl::int_<0> >(seq_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_get<boost::mpl::int_<1> >(seq_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get<boost::mpl::int_<0> >(seq_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_get<boost::mpl::int_<1> >(seq_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_get<boost::mpl::int_<0> >(seq_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_get< boost::mpl::int_<1> >(seq_t const)>::type>));

#endif



void test()
{
    pair_t p(1, 'a');
    BOOST_CHECK( is_same(p.first, pstade::tuple_get_c<0>(p)) );
    BOOST_CHECK( is_same(p.second, pstade::tuple_get_c<1>(p)) );

    tup_t t(p.first, 1.0);
    BOOST_CHECK( is_same(boost::get<0>(t), pstade::tuple_get<boost::mpl::int_<0> >(t)) );
    BOOST_CHECK( is_same(boost::get<1>(t), pstade::tuple_get<boost::mpl::int_<1> >(t)) );

    BOOST_CHECK( is_same(boost::get<0>(t), pstade::tuple_get_c<0>(t)) );
    BOOST_CHECK( is_same(boost::get<1>(t), pstade::tuple_get_c<1>(t)) );

#if defined(PSTADE_TUPLE_FUSION_SUPPORTED)
    seq_t s(p.first, 1.0);
    BOOST_CHECK( is_same(boost::fusion::at_c<0>(s), pstade::tuple_get<boost::mpl::int_<0> >(s)) );
    BOOST_CHECK( is_same(boost::fusion::at_c<1>(s), pstade::tuple_get<boost::mpl::int_<1> >(s)) );

    BOOST_CHECK( is_same(boost::fusion::at_c<0>(s), pstade::tuple_get_c<0>(s)) );
    BOOST_CHECK( is_same(boost::fusion::at_c<1>(s), pstade::tuple_get_c<1>(s)) );
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
