#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/mpl_min_max.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/static_assert.hpp>


using namespace pstade;
using boost::mpl::int_;


void pstade_minimal_test()
{
    BOOST_STATIC_ASSERT((mpl_min< int_<5>, int_<10> >::type::value == 5));
    BOOST_STATIC_ASSERT((mpl_min< int_<10>, int_<5> >::type::value == 5));

    BOOST_STATIC_ASSERT((mpl_max< int_<5>, int_<10> >::type::value == 10));
    BOOST_STATIC_ASSERT((mpl_max< int_<10>, int_<5> >::type::value == 10));

    BOOST_STATIC_ASSERT((mpl_min_c< 5, 10 >::value == 5));
    BOOST_STATIC_ASSERT((mpl_min_c< 10, 5 >::value == 5));

    BOOST_STATIC_ASSERT((mpl_max_c< 5, 10 >::value == 10));
    BOOST_STATIC_ASSERT((mpl_max_c< 10, 5 >::value == 10));
}
