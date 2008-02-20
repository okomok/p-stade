

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/if_use_default.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost::egg::details;


template< class T, class U = boost::use_default >
struct your
{
    typedef typename if_use_default<U, int>::type u_t;
    typedef typename eval_if_use_default<U, boost::mpl::identity<int> >::type u_t_;
};


typedef your<double> your_t;
BOOST_MPL_ASSERT(( boost::is_same< your_t::u_t, int > ));
BOOST_MPL_ASSERT(( boost::is_same< your_t::u_t_, int > ));


BOOST_MPL_ASSERT(( boost::is_same< if_use_default<boost::use_default, char>::type, char > ));
BOOST_MPL_ASSERT(( boost::is_same< if_use_default<boost::use_default, char, double>::type, char > ));
BOOST_MPL_ASSERT(( boost::is_same< if_use_default<int, char>::type, int > ));
BOOST_MPL_ASSERT(( boost::is_same< if_use_default<int, char, double>::type, double > ));

BOOST_MPL_ASSERT(( boost::is_same< eval_if_use_default<boost::use_default, boost::mpl::identity<char> >::type, char > ));
BOOST_MPL_ASSERT(( boost::is_same< eval_if_use_default<boost::use_default, boost::mpl::identity<char>, boost::mpl::identity<double> >::type, char > ));
BOOST_MPL_ASSERT(( boost::is_same< eval_if_use_default<int, boost::mpl::identity<char> >::type, int > ));
BOOST_MPL_ASSERT(( boost::is_same< eval_if_use_default<int, boost::mpl::identity<char>, boost::mpl::identity<double> >::type, double > ));


void egg_test()
{ }
