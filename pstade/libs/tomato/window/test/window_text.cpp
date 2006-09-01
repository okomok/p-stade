#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/window/window_text.hpp>


#include <pstade/garlic/back_inserter.hpp>
#include <pstade/tomato/garlic/customization.hpp>


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
#include <pstade/diet/reset_ostream.hpp>
#include <pstade/oven/algorithm.hpp> // copy
#include <pstade/oven/copy_range.hpp>
#include <pstade/tomato/c_str.hpp>
#include <pstade/tomato/tstring.hpp>
#include <pstade/tomato/tstream.hpp>


void test()
{
    using namespace pstade;
    using namespace tomato;

    HWND hWnd = ::GetForegroundWindow();

#if (PSTADE_APPLE_ATL_VER >= 0x0700)
    {
        ATL::CString str;
        oven::copy(tomato::window_text(hWnd), garlic::back_inserter(str));
        tcout << str << std::endl;
    }
#endif

    {
        WTL::CString str;
        oven::copy(tomato::window_text(hWnd), garlic::back_inserter(str));
        tcout << str << std::endl;
    }

    {
        tomato::window_text text(hWnd);
        std::basic_string<TCHAR> str;
        std::copy(boost::begin(text), boost::end(text), std::back_inserter(str));
        tcout << str << std::endl;
    }

    {
        tomato::window_text text(hWnd);
        // boost::to_upper(text); // no longer mutable range
        tcout << (text|c_stringized) << std::endl;
    }

    {
        typedef std::basic_string<TCHAR> tstring;
        tstring str = tomato::window_text(hWnd)|oven::copied;
        tcout << str << std::endl;
    }

    {
        tcout << (tomato::window_text(hWnd)|c_stringized) << std::endl;
    }
}


int test_main(int, char *[])
{
    pstade::diet::reset_ostream(std::cout);
    ::test();
    return 0;
}
