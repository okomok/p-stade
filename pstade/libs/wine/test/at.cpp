#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/at.hpp>


#include <boost/tuple/tuple.hpp>
#include <utility>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/is_same.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace pstade;


typedef std::pair<int, char> pair_t;

BOOST_MPL_ASSERT((boost::is_same<int, value_at_first<pair_t>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, value_at_second<pair_t>::type>));

BOOST_MPL_ASSERT((boost::is_same<int, value_at_first<pair_t const>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, value_at_second<pair_t const>::type>));

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_at_first(pair_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char&, boost::result_of<op_at_second(pair_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<op_at_first(pair_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<op_at_second(pair_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<op_at_first(pair_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<op_at_second(pair_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int const&, boost::result_of<op_at_first(pair_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const&, boost::result_of<op_at_second(pair_t const)>::type>));


typedef boost::tuples::tuple<int&, double> tup_t;

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_value_at<tup_t, boost::mpl::int_<0> >::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_value_at<tup_t, boost::mpl::int_<1> >::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, tuple_value_at<tup_t const, boost::mpl::int_<0> >::type>));
BOOST_MPL_ASSERT((boost::is_same<double, tuple_value_at<tup_t const, boost::mpl::int_<1> >::type>));

// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_at<boost::mpl::int_<0> >(tup_t&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double&, boost::result_of<op_tuple_at<boost::mpl::int_<1> >(tup_t&)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_at<boost::mpl::int_<0> >(tup_t const&)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_at<boost::mpl::int_<1> >(tup_t const&)>::type>));

// rvalue
BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_at<boost::mpl::int_<0> >(tup_t)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_at<boost::mpl::int_<1> >(tup_t)>::type>));

BOOST_MPL_ASSERT((boost::is_same<int&, boost::result_of<op_tuple_at<boost::mpl::int_<0> >(tup_t const)>::type>));
BOOST_MPL_ASSERT((boost::is_same<double const&, boost::result_of<op_tuple_at< boost::mpl::int_<1> >(tup_t const)>::type>));


void test()
{
    pair_t p(1, 'a');
    BOOST_CHECK( is_same(p.first, at_first(p)) );
    BOOST_CHECK( is_same(p.second, at_second(p)) );

    tup_t t(p.first, 1.0);
    BOOST_CHECK( is_same(boost::get<0>(t), pstade::tuple_at<boost::mpl::int_<0> >(t)) );
    BOOST_CHECK( is_same(boost::get<1>(t), pstade::tuple_at<boost::mpl::int_<1> >(t)) );

    BOOST_CHECK( is_same(boost::get<0>(t), pstade::tuple_at_c<0>(t)) );
    BOOST_CHECK( is_same(boost::get<1>(t), pstade::tuple_at_c<1>(t)) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
