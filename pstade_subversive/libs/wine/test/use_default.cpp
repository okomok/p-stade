#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/use_default.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace pstade;


template< class T, class U = boost::use_default >
struct your
{
    typedef typename use_default_to<U, int>::type u_t;
    typedef typename use_default_eval_to<U, boost::mpl::identity<int> >::type u_t_;
};


typedef your<double> your_t;
BOOST_MPL_ASSERT(( boost::is_same< your_t::u_t, int > ));
BOOST_MPL_ASSERT(( boost::is_same< your_t::u_t_, int > ));


int test_main(int, char*[])
{
    return 0;
}
