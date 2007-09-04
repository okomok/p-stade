#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/tuple/pack_by_ref.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>


BOOST_MPL_ASSERT(( boost::is_same< boost::tuples::tuple<>,
                 pstade::result_of<pstade::egg::op_tuple_pack_by_ref()>::type > ));

BOOST_MPL_ASSERT(( boost::is_same< boost::tuples::tuple<int&, int const&>,
                 pstade::result_of<pstade::egg::op_tuple_pack_by_ref(int&, int const&)>::type > ));


void pstade_minimal_test()
{
    using namespace pstade::egg;

    int const i0 = 0, i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    int i5 = 5, i6 = 6, i7 = 7, i8 = 8, i9 = 9;

    BOOST_CHECK( boost::make_tuple(i0,i1,i2,i3,i4,i5) == tuple_pack_by_ref(i0,i1,i2,i3,i4,i5) );
    BOOST_CHECK( boost::make_tuple(i0,i1,i2,i3,i4)    == tuple_pack_by_ref(i0,i1,i2,i3,i4)   );
    BOOST_CHECK( boost::make_tuple(i0,i1,i2,i3)       == tuple_pack_by_ref(i0,i1,i2,i3)     );
    BOOST_CHECK( boost::make_tuple(i0,i1,i2)          == tuple_pack_by_ref(i0,i1,i2)       );
    BOOST_CHECK( boost::make_tuple(i0,i1)             == tuple_pack_by_ref(i0,i1)         );
    BOOST_CHECK( boost::make_tuple()                  == tuple_pack_by_ref()          );

    BOOST_CHECK( &(boost::tuples::get<0>(tuple_pack_by_ref(i0,i1,i2,i3,i4,i5))) == &i0 );
    BOOST_CHECK( &(boost::tuples::get<5>(tuple_pack_by_ref(i0,i1,i2,i3,i4,i5))) == &i5 );
}
