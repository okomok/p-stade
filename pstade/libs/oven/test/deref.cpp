#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/deref.hpp>


#include "./core.hpp"
#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


namespace oven = pstade::oven;
using namespace oven;


// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, deref_detail::result_<int, int&>::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, deref_detail::result_<int, int const&>::type>));

// readable
BOOST_MPL_ASSERT((boost::is_same<int, deref_detail::result_<int, int>::type>));
BOOST_MPL_ASSERT((boost::is_same<int, deref_detail::result_<int, int const>::type>));
BOOST_MPL_ASSERT((boost::is_same<int, deref_detail::result_<int, char&>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, deref_detail::result_<char, int&>::type>));
BOOST_MPL_ASSERT((boost::is_same<int, deref_detail::result_<int, char const&>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, deref_detail::result_<char, int const&>::type>));
BOOST_MPL_ASSERT((boost::is_same<int, deref_detail::result_<int, char const>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, deref_detail::result_<char, int const>::type>));
BOOST_MPL_ASSERT((boost::is_same<int, deref_detail::result_<int, char>::type>));
BOOST_MPL_ASSERT((boost::is_same<char, deref_detail::result_<char, int>::type>));


void test()
{
    {
        std::string rng("abcdefg");
        deref(boost::begin(rng)) = 'x';
        BOOST_CHECK( equals(rng, std::string("xbcdefg")) );
    }
    {
        int rng[] = { 1,2,3 };
        BOOST_CHECK( &deref(boost::begin(rng)) == &rng[0] );
    }
    {
        int const rng[] = { 1,2,3 };
        BOOST_CHECK( &deref(boost::begin(rng)) == &rng[0] );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
