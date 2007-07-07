#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp> // include first for Win32 Boost.Test


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/size_initialize.hpp>


#include <pstade/gravy/sdk/windows.hpp>


namespace gravy = pstade::gravy;
using namespace gravy;


void pstade_minimal_test()
{
    {
        WNDCLASSEX x;
        size_initialize(x);
        BOOST_CHECK(x.cbSize == sizeof(WNDCLASSEX));
    }
    {
        MENUITEMINFO x;
        size_initialize(x);
        BOOST_CHECK(x.cbSize == sizeof(MENUITEMINFO));
    }
    {
        MENUITEMINFO x;
        x|size_initialize();
        BOOST_CHECK(x.cbSize == sizeof(MENUITEMINFO));
    }
#if !defined(_WIN32_WCE)
    {
        WINDOWPLACEMENT x;
        size_initialize(x);
        BOOST_CHECK(x.length == sizeof(WINDOWPLACEMENT));
    }
#endif
}
