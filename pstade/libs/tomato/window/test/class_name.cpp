#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/window/class_name.hpp>


#include <pstade/garlic/back_inserter.hpp>
#include <pstade/tomato/garlic/customization.hpp>


#include <iostream>
#include <pstade/apple/atl/str.hpp>
#include <pstade/apple/atl/config.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/misc.hpp>
#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;
#include <pstade/oven/algorithm.hpp> // copy


void test()
{
    using namespace pstade;

    HWND hWnd = ::GetForegroundWindow();

#if (PSTADE_APPLE_ATL_VER >= 0x0700)
    {
        ATL::CString str;
        oven::copy(tomato::class_name(hWnd), garlic::back_inserter(str));
        std::cout << str << std::endl;
    }
#endif

    {
        WTL::CString str;
        oven::copy(tomato::class_name(hWnd), garlic::back_inserter(str));
        std::cout << str << std::endl;
    }
}


int test_main(int, char *[])
{
    ::test();
    return 0;
}
