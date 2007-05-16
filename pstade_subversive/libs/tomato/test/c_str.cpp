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


#include <pstade/tomato/c_str.hpp>


#include <iostream>
#include <pstade/apple/wtl/misc.hpp> // CString
#include <pstade/tomato/tstring.hpp>
#include <pstade/tomato/window.hpp>
#include <pstade/tomato/filesystem.hpp>
#include <boost/mpl/assert.hpp>


struct a_string : pstade::tomato::tstring
{ };


void test()
{
    using namespace pstade;
    using namespace tomato;
    
    tstring ans(_T("abcde"));

    {
        tstring str(_T("abcde"));
        BOOST_CHECK( ans == tomato::c_str(str) );

        // maybe rejected. op()| can be ambiguous. 
        BOOST_CHECK( ans == (str|c_str) );
    }
    
    {
        TCHAR str[] = _T("abcde");
        BOOST_CHECK( ans == tomato::c_str(str) );
        BOOST_CHECK( ans == (str|c_str) );
    }

    {
        WTL::CString str(_T("abcde"));
        BOOST_CHECK( ans == tomato::c_str(str) );
        BOOST_CHECK( ans == (str|c_str) );
    }

    {
        HWND hWnd = ::GetForegroundWindow();
        std::cout << tomato::c_str(tomato::window_text(hWnd)) << std::endl;
        std::cout << (tomato::window_text(hWnd)|c_str) << std::endl;
    }

    {
        ::a_string str;
        tomato::c_str(str);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
