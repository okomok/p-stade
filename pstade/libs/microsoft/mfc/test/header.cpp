///////////////////////////////////////////////////////////////////////////////
// Boost.Range support for Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#define _WIN32_WINNT 0x0400 // for <boost/test/minimal.hpp>
#define _AFXDLL

#include <afx.h>


#include <afxcoll.h>
#if (_MFC_VER >= 0x0700)
    #include <afxstr.h>
#endif
#include <afxtempl.h>

#include <boost/test/minimal.hpp>
#include <boost/microsoft/mfc.hpp>


int test_main(int, char*[])
{
    return 0;
}
