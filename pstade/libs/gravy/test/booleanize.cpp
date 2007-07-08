#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp> // include first for Win32 Boost.Test


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/booleanize.hpp>


#include <iostream>


void pstade_minimal_test()
{
    using pstade::gravy::booleanize;

    {
        bool t, f;
        t = true|booleanize();
        f = false|booleanize;
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
        t = TRUE|booleanize();
        f = FALSE|booleanize();
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
        t = VARIANT_TRUE|booleanize();
        f = VARIANT_FALSE|booleanize;
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
    }

    {
        BOOL t, f;
        t = true|booleanize();
        f = false|booleanize();
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = TRUE|booleanize;
        f = FALSE|booleanize();
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = VARIANT_TRUE|booleanize();
        f = VARIANT_FALSE|booleanize();
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
    }

    {
        VARIANT_BOOL t, f;
        t = true|booleanize();
        f = false|booleanize();
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
        t = TRUE|booleanize();
        f = FALSE|booleanize;
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
        t = VARIANT_TRUE|booleanize();
        f = VARIANT_FALSE|booleanize();
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
    }

    {
        BOOLEAN t, f;
        t = true|booleanize();
        f = false|booleanize();
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = TRUE|booleanize();
        f = FALSE|booleanize();
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = VARIANT_TRUE|booleanize();
        f = VARIANT_FALSE|booleanize();
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
    }
}
