#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/optional.hpp>


#include <pstade/minimal_test.hpp>
#include <boost/optional/optional.hpp>
#include "./detail/test.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/equals.hpp>


namespace oven = pstade::oven;
using namespace oven;


BOOST_MPL_ASSERT((boost::is_same<range_iterator<boost::optional<int> >::type, int *>));
BOOST_MPL_ASSERT((boost::is_same<range_iterator<boost::optional<int &> >::type, int *>));
BOOST_MPL_ASSERT((boost::is_same<range_iterator<boost::optional<int const &> >::type, int const *>));

BOOST_MPL_ASSERT((boost::is_same<range_iterator<boost::optional<int> const>::type, int const *>));
BOOST_MPL_ASSERT((boost::is_same<range_iterator<boost::optional<int &> const>::type, int *>));
BOOST_MPL_ASSERT((boost::is_same<range_iterator<boost::optional<int const &> const>::type, int const *>));


void pstade_minimal_test()
{
    {
        boost::optional<int> b(12);

        BOOST_CHECK( distance(b) == 1 );
        int a[] = {12};
        BOOST_CHECK( equals(a, b) );

        BOOST_CHECK( *boost::begin(b) == 12 );
        BOOST_CHECK( &*boost::begin(b) == &*b );
        *boost::begin(b) = 13;
        BOOST_CHECK( *b == 13 );
    }
    {
        int i = 12;
        boost::optional<int&> b(i);

        BOOST_CHECK( distance(b) == 1 );
        int a[] = {12};
        BOOST_CHECK( equals(a, b) );

        BOOST_CHECK( *boost::begin(b) == 12 );
        BOOST_CHECK( &*boost::begin(b) == &i );
        *boost::begin(b) = 13;
        BOOST_CHECK( *b == 13 );
        BOOST_CHECK( i == 13 );

        // const doesn't affect
        *boost::const_begin(b) = 14;
        BOOST_CHECK( *b == 14 );
        BOOST_CHECK( i == 14 );
    }
    {
        int const i = 12;
        boost::optional<int const&> b(i);

        BOOST_CHECK( distance(b) == 1 );
        int a[] = {12};
        BOOST_CHECK( equals(a, b) );

        BOOST_CHECK( distance(b) == 1 );
        BOOST_CHECK( *boost::begin(b) == 12 );
        BOOST_CHECK( &*boost::begin(b) == &i );
    }

    {
        boost::optional<int> b;
        test::emptiness(b);
    }
    {
        boost::optional<int &> b;
        test::emptiness(b);
    }
    {
        boost::optional<int const &> b;
        test::emptiness(b);
    }
}
