#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/tuple_pack.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>


BOOST_MPL_ASSERT(( boost::is_same< boost::tuples::tuple<>,
                 boost::result_of<pstade::egg::op_tuple_pack()>::type > ));

BOOST_MPL_ASSERT(( boost::is_same< boost::tuples::tuple<int&, int const&>,
                 boost::result_of<pstade::egg::op_tuple_pack(int&, int)>::type > ));


void pstade_minimal_test()
{
    using namespace pstade::egg;

    BOOST_CHECK( boost::make_tuple(1,2,3,4,5) == tuple_pack(1,2,3,4,5) );
    BOOST_CHECK( boost::make_tuple(1,2,3,4)   == tuple_pack(1,2,3,4)   );
    BOOST_CHECK( boost::make_tuple(1,2,3)     == tuple_pack(1,2,3)     );
    BOOST_CHECK( boost::make_tuple(1,2)       == tuple_pack(1,2)       );
    BOOST_CHECK( boost::make_tuple(1)         == tuple_pack(1)         );
    BOOST_CHECK( boost::make_tuple()          == tuple_pack()          );

    {
        int m = 5;
        boost::tuples::get<4>(tuple_pack(1,2,3,4,m)) = 10;
        BOOST_CHECK(m == 10);
    }
    {
        int x, y, z;
        tuple_pack(x, y, z) = tuple_pack(1, 2, 3);
        BOOST_CHECK( x == 1 && y == 2 && z == 3 );
    }
}
