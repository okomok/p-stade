#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>
#include <boost/microsoft/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/c_str.hpp>


#include <iostream>
#include <boost/microsoft/wtl/misc.hpp> // CString
#include <pstade/tomato/tstring.hpp>
#include <pstade/tomato/window.hpp>
#include <pstade/tomato/filesystem.hpp>


// should be?
#define ADAPTOR_SYNTAX_ACCEPTED(Expr) Expr


void test()
{
    using namespace pstade;
    using namespace tomato;
    
    tstring ans(_T("abcde"));

    {
        tstring str(_T("abcde"));
        BOOST_CHECK( ans == tomato::c_str(str) );

        // maybe rejected. op()| can be ambiguous. 
        BOOST_CHECK( ans == (str|c_stringized) );
    }
    
    {
        TCHAR str[] = _T("abcde");
        BOOST_CHECK( ans == tomato::c_str(str) );
        ADAPTOR_SYNTAX_ACCEPTED( BOOST_CHECK( ans == (str|c_stringized) ); )
    }

    {
        WTL::CString str(_T("abcde"));
        BOOST_CHECK( ans == tomato::c_str(str) );
        ADAPTOR_SYNTAX_ACCEPTED( BOOST_CHECK( ans == (str|c_stringized) ); )
    }

    {
        HWND hWnd = ::GetForegroundWindow();
        std::cout << tomato::c_str(tomato::window_text(hWnd)) << std::endl;
        ADAPTOR_SYNTAX_ACCEPTED( std::cout << (tomato::window_text(hWnd)|c_stringized) << std::endl; )
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
