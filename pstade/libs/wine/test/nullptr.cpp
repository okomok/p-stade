#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/nullptr.hpp>
#include <boost/test/minimal.hpp>


void test()
{
    using namespace pstade;

    BOOST_CHECK( PSTADE_NULLPTR == 0 );
    BOOST_CHECK( !PSTADE_NULLPTR );

    BOOST_CHECK( nullptr_<int>() == 0);
    BOOST_CHECK( nullptr_<int const>() == 0);
    BOOST_CHECK( null_<int *>() == 0);
    BOOST_CHECK( null_<int const *>() == 0);

    BOOST_CHECK( nullptr_<int>() == null_<int *>() );
    BOOST_CHECK( nullptr_<int const>() == null_<int const *>() );

    int i = 10;
    int *p = &i;
    BOOST_CHECK( PSTADE_NULLPTR != p );
    BOOST_CHECK( nullptr_<int>() != p);
    BOOST_CHECK( nullptr_<int const>() != p);
    BOOST_CHECK( null_<int *>() != p);
    BOOST_CHECK( null_<int const *>() != p);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
