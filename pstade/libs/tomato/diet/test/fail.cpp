#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <windows.h>
#include <cassert>
#include <pstade/diet.hpp>
#include <pstade/tomato/diet/customization.hpp>
#include <pstade/tomato/diet/buffer.hpp>
#include <pstade/check.hpp>
#include <pstade/require.hpp>


void test_fail()
{
    using namespace pstade;


    try {
        HWND dg = (HWND)0x12345;
        //assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
    }
    catch (...)
    {
    }

    try {
        HDC dg = NULL;
        //assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
    }
    catch (...)
    {
    }


    try {
        const TCHAR *dg = NULL;
        //assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
    }
    catch (...)
    {
    }

    try {
        TCHAR *dg = NULL;
        //assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
    }
    catch (...)
    {
    }

    try {
        HWND dg[] = { NULL, NULL };
        //assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
    }
    catch (...)
    {
    }

}


int test_main(int, char*[])
{
    pstade::check_reset_ostream(std::cout);
    pstade::diet::reset_ostream(std::cout);
    ::test_fail();
    return 0;
}
