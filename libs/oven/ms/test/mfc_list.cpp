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

#include <afxcoll.h>
#include <afxtempl.h>


#include <boost/test/minimal.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    // VC++7.1 fatal error C1204
    #define PSTADE_OVEN_TESTS_NO_CONCEPT_CHECK
#endif

#include "../../test/detail/v1_tests.hpp"
#include <pstade/oven/mfc.hpp>


#include <pstade/oven/const_refs.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    { // CList
        int ans[] = { 0,1,2,3,4,5,6,7 };
        std::vector<int> expected = ans|copied;
        CList<int, const int&> rng; {
            rng.AddTail(0), rng.AddTail(1), rng.AddTail(2), rng.AddTail(3),
            rng.AddTail(4), rng.AddTail(5), rng.AddTail(6), rng.AddTail(7);
        }

#if !defined(PSTADE_APPLE_MFC_CONST_COL_RETURNS_NON_REF)
        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
            rng,
            expected
        ) );
#else
        // In fact, it is *Bidirectional Input* which 'test_xxx' cannot handle yet.
        // So remove *Input* ness by using 'const_refs'.
        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|const_refs,
            expected
        ) );
#endif
    }
    { // CStringList
        CString ans[] = {
            CString(_T('0')), CString(_T('1')), CString(_T('2')), CString(_T('3')),
            CString(_T('4')), CString(_T('5')), CString(_T('6')), CString(_T('7'))
        };
        std::vector<CString> expected = ans|copied;

        CStringList rng; {
            rng.AddTail(ans[0]), rng.AddTail(ans[1]), rng.AddTail(ans[2]), rng.AddTail(ans[3]),
            rng.AddTail(ans[4]), rng.AddTail(ans[5]), rng.AddTail(ans[6]), rng.AddTail(ans[7]);
        }

#if !defined(PSTADE_APPLE_MFC_CONST_COL_RETURNS_NON_REF)
        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
            rng,
            expected
        ) );
#else
        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|const_refs,
            expected
        ) );
#endif
    }
    { // CObList
        CObject *ans[] = {
            new CObList(), new CObList(), new CObList()
        };

        // The 'value_type' of 'CObList' and 'CObList const' is differenct.
        // So _Writable test can't restore the value...

        std::vector<CObject const *> expected = ans|copied;

        CObList rng; {
            rng.AddTail(ans[0]), rng.AddTail(ans[1]), rng.AddTail(ans[2]);
        }

#if !defined(PSTADE_APPLE_MFC_CONST_COL_RETURNS_NON_REF)
        BOOST_CHECK( oven::test_Bidirectional_Readable( // _Writable(
            rng,
            expected
        ) );
#else
        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|const_refs,
            expected
        ) );
#endif
    }
    { // CPtrList
        void *ans[] = {
            new CObList(), new CObList(), new CObList()
        };

        std::vector<void const *> expected = ans|copied;

        CPtrList rng; {
            rng.AddTail(ans[0]), rng.AddTail(ans[1]), rng.AddTail(ans[2]);
        }

#if !defined(PSTADE_APPLE_MFC_CONST_COL_RETURNS_NON_REF)
        BOOST_CHECK( oven::test_Bidirectional_Readable( // _Writable(
            rng,
            expected
        ) );
#else
        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|const_refs,
            expected
        ) );
#endif
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
