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


void test_basic()
{
    using namespace pstade;

    {
        HWND dg = ::GetDesktopWindow();
        assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
        BOOST_CHECK(diet::valid(dg));
    }

    {
        HDC dg = ::GetDC(::GetDesktopWindow());
        assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
        BOOST_CHECK(diet::valid(dg));
    }


    {
        const TCHAR *dg = _T("valid string");
        assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
        BOOST_CHECK( diet::valid(dg) );
    }

    {
        TCHAR arr[] = { _T('a'), _T('b'), _T('c') ,_T('\0') };
        TCHAR *dg = arr;
        assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
        BOOST_CHECK( diet::valid(dg) );
    }

    {
        int arr[5];
        tomato::buffer dg(arr);
        assert(diet::valid(dg));
        PSTADE_CHECK(diet::valid(dg));
        PSTADE_REQUIRE(diet::valid(dg) && "error!");
        BOOST_CHECK( diet::valid(dg) );
    }
}


int test_main(int, char*[])
{
    ::test_basic();
    return 0;
}
