#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/read.hpp>


#include "./detail/v1_core.hpp"
#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/iterator.hpp>

namespace oven = pstade::oven;
using namespace oven;


template<class V, class R>
struct an_iterator :
    boost::iterator<
        std::forward_iterator_tag, V, std::ptrdiff_t, V const*, R
    >
{ };


// lvalue
BOOST_MPL_ASSERT((boost::is_same<int&, iterator_read< an_iterator<int, int&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, iterator_read< an_iterator<int, int const&> >::type>));

// readable
BOOST_MPL_ASSERT((boost::is_same<int, iterator_read< an_iterator <int, int> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int, iterator_read< an_iterator<int, int const> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int, iterator_read< an_iterator<int, char&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<char, iterator_read< an_iterator<char, int&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int, iterator_read< an_iterator<int, char const&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<char, iterator_read< an_iterator<char, int const&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int, iterator_read< an_iterator<int, char const> >::type>));
BOOST_MPL_ASSERT((boost::is_same<char, iterator_read< an_iterator<char, int const> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int, iterator_read< an_iterator<int, char> >::type>));
BOOST_MPL_ASSERT((boost::is_same<char, iterator_read< an_iterator<char, int> >::type>));


void test()
{
    {
        std::string rng("abcdefg");
        read(boost::begin(rng)) = 'x';
        BOOST_CHECK( equals(rng, std::string("xbcdefg")) );
    }
    {
        int rng[] = { 1,2,3 };
        BOOST_CHECK( &read(boost::begin(rng)) == &rng[0] );
    }
    {
        int const rng[] = { 1,2,3 };
        BOOST_CHECK( &read(boost::begin(rng)) == &rng[0] );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
