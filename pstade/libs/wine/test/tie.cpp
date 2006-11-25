#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tie.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>


void test()
{
    using namespace pstade;

    BOOST_CHECK( boost::make_tuple(1,2,3,4,5) == tie(1,2,3,4,5) );
    BOOST_CHECK( boost::make_tuple(1,2,3,4)   == tie(1,2,3,4)   );
    BOOST_CHECK( boost::make_tuple(1,2,3)     == tie(1,2,3)     );
    BOOST_CHECK( boost::make_tuple(1,2)       == tie(1,2)       );
    BOOST_CHECK( boost::make_tuple(1)         == tie(1)         );

    BOOST_CHECK( boost::make_tuple(1,2,3,4,5) == (1|tied(2,3,4,5)) );
    BOOST_CHECK( boost::make_tuple(1,2,3,4)   == (1|tied(2,3,4))   );
    BOOST_CHECK( boost::make_tuple(1,2,3)     == (1|tied(2,3))     );
    BOOST_CHECK( boost::make_tuple(1,2)       == (1|tied(2))       );
    BOOST_CHECK( boost::make_tuple(1)         == (1|tied())        );
    BOOST_CHECK( boost::make_tuple(1)         == (1|tied)          );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
