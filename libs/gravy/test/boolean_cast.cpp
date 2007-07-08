#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp> // include first for Win32 Boost.Test


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/boolean_cast.hpp>


#include <iostream>


void test_boolean_cast()
{
    using pstade::gravy::boolean_cast;

    // to bool
    BOOST_CHECK( boolean_cast<bool>(true) == true );
    BOOST_CHECK( boolean_cast<bool>(false) == false );
    BOOST_CHECK( boolean_cast<bool>(TRUE) == true );
    BOOST_CHECK( boolean_cast<bool>(FALSE) == false );
    BOOST_CHECK( boolean_cast<bool>(VARIANT_TRUE) == true );
    BOOST_CHECK( boolean_cast<bool>(VARIANT_FALSE) == false );

    // to BOOL
    BOOST_CHECK( boolean_cast<BOOL>(true) == TRUE );
    BOOST_CHECK( boolean_cast<BOOL>(false) == FALSE );
    BOOST_CHECK( boolean_cast<BOOL>(TRUE) == TRUE );
    BOOST_CHECK( boolean_cast<BOOL>(FALSE) == FALSE );
    BOOST_CHECK( boolean_cast<BOOL>(VARIANT_TRUE) == TRUE );
    BOOST_CHECK( boolean_cast<BOOL>(VARIANT_FALSE) == FALSE );

    // to VARIANT_BOOL
    BOOST_CHECK( boolean_cast<VARIANT_BOOL>(true) == VARIANT_TRUE );
    BOOST_CHECK( boolean_cast<VARIANT_BOOL>(false) == VARIANT_FALSE );
    BOOST_CHECK( boolean_cast<VARIANT_BOOL>(TRUE) == VARIANT_TRUE );
    BOOST_CHECK( boolean_cast<VARIANT_BOOL>(FALSE) == VARIANT_FALSE );
    BOOST_CHECK( boolean_cast<VARIANT_BOOL>(VARIANT_TRUE) == VARIANT_TRUE );
    BOOST_CHECK( boolean_cast<VARIANT_BOOL>(VARIANT_FALSE) == VARIANT_FALSE );

    // to BOOLEAN
    BOOST_CHECK( boolean_cast<BOOLEAN>(true) == TRUE );
    BOOST_CHECK( boolean_cast<BOOLEAN>(false) == FALSE );
    BOOST_CHECK( boolean_cast<BOOLEAN>(TRUE) == TRUE );
    BOOST_CHECK( boolean_cast<BOOLEAN>(FALSE) == FALSE );
    BOOST_CHECK( boolean_cast<BOOLEAN>(VARIANT_TRUE) == TRUE );
    BOOST_CHECK( boolean_cast<BOOLEAN>(VARIANT_FALSE) == FALSE );
}


void test_compare()
{
#if 0
    using namespace pstade;
    using namespace gravy;

    BOOL volatile b = TRUE;
    bool t0 = b ? true : false;

    bool t1 = gravy::boolean_cast<bool>(b); // faster than 't0' code.
    bool t2 = gravy::boolean(b); // has function call.
    bool t3 = b|booleanize(); // nearly same as above.

    std::cout << t0 << t1 << t2 << t3;
#endif
}


void pstade_minimal_test()
{
    ::test_boolean_cast();
    ::test_compare();
}
