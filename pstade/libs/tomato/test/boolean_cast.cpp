#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/boolean_cast.hpp>


#include <iostream>


void test_boolean_cast()
{
    using namespace pstade::tomato;

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


void test_boolean()
{
    using namespace pstade;

    {
        bool t, f;
        t = tomato::boolean(true);
        f = tomato::boolean(false);
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
        t = tomato::boolean(TRUE);
        f = tomato::boolean(FALSE);
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
        t = tomato::boolean(VARIANT_TRUE);
        f = tomato::boolean(VARIANT_FALSE);
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
    }

    {
        BOOL t, f;
        t = tomato::boolean(true);
        f = tomato::boolean(false);
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = tomato::boolean(TRUE);
        f = tomato::boolean(FALSE);
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = tomato::boolean(VARIANT_TRUE);
        f = tomato::boolean(VARIANT_FALSE);
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
    }

    {
        VARIANT_BOOL t, f;
        t = tomato::boolean(true);
        f = tomato::boolean(false);
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
        t = tomato::boolean(TRUE);
        f = tomato::boolean(FALSE);
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
        t = tomato::boolean(VARIANT_TRUE);
        f = tomato::boolean(VARIANT_FALSE);
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
    }

    {
        BOOLEAN t, f;
        t = tomato::boolean(true);
        f = tomato::boolean(false);
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = tomato::boolean(TRUE);
        f = tomato::boolean(FALSE);
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = tomato::boolean(VARIANT_TRUE);
        f = tomato::boolean(VARIANT_FALSE);
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
    }
}


void test_booleanized()
{
    using namespace pstade;
    using namespace tomato;

    {
        bool t, f;
        t = true|booleanized;
        f = false|booleanized;
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
        t = TRUE|booleanized;
        f = FALSE|booleanized;
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
        t = VARIANT_TRUE|booleanized;
        f = VARIANT_FALSE|booleanized;
        BOOST_CHECK( t == true );
        BOOST_CHECK( f == false );
    }

    {
        BOOL t, f;
        t = true|booleanized;
        f = false|booleanized;
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = TRUE|booleanized;
        f = FALSE|booleanized;
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = VARIANT_TRUE|booleanized;
        f = VARIANT_FALSE|booleanized;
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
    }

    {
        VARIANT_BOOL t, f;
        t = true|booleanized;
        f = false|booleanized;
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
        t = TRUE|booleanized;
        f = FALSE|booleanized;
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
        t = VARIANT_TRUE|booleanized;
        f = VARIANT_FALSE|booleanized;
        BOOST_CHECK( t == VARIANT_TRUE );
        BOOST_CHECK( f == VARIANT_FALSE );
    }

    {
        BOOLEAN t, f;
        t = true|booleanized;
        f = false|booleanized;
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = TRUE|booleanized;
        f = FALSE|booleanized;
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
        t = VARIANT_TRUE|booleanized;
        f = VARIANT_FALSE|booleanized;
        BOOST_CHECK( t == TRUE );
        BOOST_CHECK( f == FALSE );
    }
}


void test_compare()
{
    using namespace pstade;
    using namespace tomato;

    BOOL volatile b = TRUE;
    bool t0 = b ? true : false;

    bool t1 = tomato::boolean_cast<bool>(b); // faster than 't0' code.
    bool t2 = tomato::boolean(b); // has function call.
    bool t3 = b|booleanized; // nearly same as above.

    std::cout << t0 << t1 << t2 << t3;
}


int test_main(int, char*[])
{
    ::test_boolean_cast();
    ::test_boolean();
    ::test_booleanized();
    ::test_compare();
    return 0;
}
