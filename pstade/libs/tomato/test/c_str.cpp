#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#include <pstade/tomato/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/gravy_c_str.hpp>
#include <pstade/gravy/c_str.hpp>


#include <iostream>
#include <pstade/tomato/wtl/misc.hpp> // CString
#include <pstade/gravy/tstring.hpp>
#include <pstade/gravy/window_text.hpp>


struct a_string : pstade::gravy::tstring
{ };


void test()
{
    using namespace pstade;

    gravy::tstring ans(_T("abcde"));

    {
        gravy::tstring str(_T("abcde"));
        BOOST_CHECK( ans == gravy::c_str(str) );

        // maybe rejected. op()| can be ambiguous. 
        BOOST_CHECK( ans == (str|gravy::c_str) );
    }
    
    {
        TCHAR str[] = _T("abcde");
        BOOST_CHECK( ans == gravy::c_str(str) );
        BOOST_CHECK( ans == (str|gravy::c_str) );
    }

    {
        WTL::CString str(_T("abcde"));
        BOOST_CHECK( ans == gravy::c_str(str) );
        BOOST_CHECK( ans == (str|gravy::c_str) );
    }

    {
        HWND hWnd = ::GetForegroundWindow();
        std::cout << gravy::c_str(gravy::window_text(hWnd)) << std::endl;
        std::cout << (gravy::window_text(hWnd)|gravy::c_str) << std::endl;
    }

    {
        ::a_string str;
        gravy::c_str(str);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
