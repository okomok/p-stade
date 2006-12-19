#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/functional.hpp>


#include <string>


std::string add_str(std::string left, std::string right)
{
    return left + right;
}




void test()
{
    BOOST_CHECK( pstade::identity(12) == 12 );

    BOOST_CHECK( pstade::not_(pstade::is_zero)(10) ); 

    BOOST_CHECK( pstade::always(3)() == 3 );

    BOOST_CHECK( pstade::equal_to(1, 1) );
    BOOST_CHECK(!pstade::equal_to(0, 1) );

    BOOST_CHECK( pstade::greater(3, 0) );
    BOOST_CHECK(!pstade::greater(1, 3) );
    BOOST_CHECK( pstade::less(0, 3) );
    BOOST_CHECK(!pstade::less(3, 1) );

    BOOST_CHECK( pstade::greater_equal(3, 0) );
    BOOST_CHECK( pstade::greater_equal(1, 1) );
    BOOST_CHECK( pstade::less_equal(0, 0) );
    BOOST_CHECK( pstade::less_equal(0, 1) );

    BOOST_CHECK( pstade::logical_and(pstade::equal_to(0, 0), pstade::greater(3, 0)) );
    BOOST_CHECK( pstade::logical_or(pstade::equal_to(0, 3), pstade::greater(3, 0)) );
    BOOST_CHECK( pstade::logical_not(pstade::equal_to(0, 3)) );

    BOOST_CHECK( pstade::is_zero(0) );
    BOOST_CHECK(!pstade::is_zero(1) );

    BOOST_CHECK( pstade::plus(3, 1) == 4 );

    std::pair<int, int> aPair(5, 7);
    BOOST_CHECK( pstade::at_first(aPair)  == 5 );
    BOOST_CHECK( pstade::at_second(aPair) == 7 );

    BOOST_CHECK(
        pstade::flip(&::add_str)("def", "abc") ==
            ::add_str("abc", "def")
    );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
