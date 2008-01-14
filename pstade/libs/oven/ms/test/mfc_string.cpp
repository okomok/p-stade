#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#define _WIN32_WINNT 0x0400 // for <boost/test/minimal.hpp>
#define _AFXDLL

#include <afx.h>

#include <algorithm>
#include <string>
#include <boost/range.hpp>


#if (_MFC_VER >= 0x0700)
    #include <afxstr.h>
#endif


#include <boost/test/minimal.hpp>


#include "../../test/detail/v1_tests.hpp"
#include <pstade/oven/mfc.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    std::basic_string<TCHAR> sample(_T("abcdefgh"));

    {
        typedef ::CString rng_t;

        std::vector<TCHAR> expected = sample|copied;
        BOOST_CHECK(( oven::test_Copyable<rng_t>(sample) ));
        rng_t rng = sample|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
