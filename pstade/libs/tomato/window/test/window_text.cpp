#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/window/window_text.hpp>


#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/wtl.hpp>

#include <iostream>
#include <iterator>
#include <string>
#include <boost/range.hpp>
#include <pstade/apple/atl/str.hpp>
#include <pstade/apple/atl/config.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/misc.hpp>
#include <pstade/apple/wtl/app.hpp>
#include <boost/algorithm/string.hpp>
#include <pstade/napkin/dout.hpp>
#include <pstade/tomato/c_str.hpp>
#include <pstade/tomato/tstring.hpp>
#include <pstade/tomato/tstream.hpp>
#include <pstade/oven.hpp>


void test()
{
    using namespace pstade;
    using namespace tomato;

    HWND hWnd = ::GetForegroundWindow();

#if (PSTADE_APPLE_ATL_VER >= 0x0700)
    {
        ATL::CString str = tomato::window_text(hWnd)|oven::copied;
        tcout << (str|to_c_str) << std::endl;
    }
#endif

    {
        WTL::CString str = tomato::window_text(hWnd)|oven::copied;
        tcout << (str|to_c_str) << std::endl;
    }

    {
        tomato::window_text text(hWnd);
        std::basic_string<TCHAR> str = text|oven::copied;
        tcout << str << std::endl;
    }

    {
        tomato::window_text text(hWnd);
        // boost::to_upper(text); // no longer mutable range
        tcout << (text|to_c_str) << std::endl;
    }

    {
        typedef std::basic_string<TCHAR> tstring;
        tstring str = tomato::window_text(hWnd)|oven::copied;
        tcout << str << std::endl;
    }

    {
        tcout << (tomato::window_text(hWnd)|to_c_str) << std::endl;
        oven::copy(tomato::window_text(hWnd), oven::to_stream(tcout));
    }
}


int test_main(int, char *[])
{
    ::test();
    return 0;
}
