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


#include "../../test/detail/v1_tests.hpp"
#include <pstade/oven/mfc.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    { // CArray
        int ans[] = { 0,1,2,3,4,5,6,7 };
        std::vector<int> expected = ans|copied;
        CArray<int, const int&> rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    { // CByteArray
        BYTE ans[] = { 0,1,2,3,4,5,6,7 };
        std::vector<BYTE> expected = ans|copied;
        CByteArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    { // CDWordArray
        DWORD ans[] = { 0,1,2,3,4,5,6,7 };
        std::vector<DWORD> expected = ans|copied;
        CDWordArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    { // CUintArray
        UINT ans[] = { 0,1,2,3,4,5,6,7 };
        std::vector<UINT> expected = ans|copied;
        CUIntArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    { // CWordArray
        WORD ans[] = { 0,1,2,3,4,5,6,7 };
        std::vector<WORD> expected = ans|copied;
        CWordArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    { // CStringArray
        CString ans[] = {
            CString(_T('0')), CString(_T('1')), CString(_T('2')), CString(_T('3')),
            CString(_T('4')), CString(_T('5')), CString(_T('6')), CString(_T('7'))
        };
        std::vector<CString> expected = ans|copied;

        CStringArray rng; {
            rng.Add(ans[0]), rng.Add(ans[1]), rng.Add(ans[2]), rng.Add(ans[3]),
            rng.Add(ans[4]), rng.Add(ans[5]), rng.Add(ans[6]), rng.Add(ans[7]);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    { // CObArray
        CObject *ans[] = {
            new CObArray(), new CObArray(), new CObArray()
        };

        // The 'value_type' of 'CObArray' and 'CObArray const' is differenct.
        // So _Writable test can't restore the value...doh!

        std::vector<CObject const *> expected = ans|copied;

        CObArray rng; {
            rng.Add(ans[0]), rng.Add(ans[1]), rng.Add(ans[2]);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable( // _Writable(
            rng,
            expected
        ) );
    }
    { // CPtrArray
        void *ans[] = {
            new CObArray(), new CObArray(), new CObArray()
        };

        std::vector<void const *> expected = ans|copied;

        CPtrArray rng; {
            rng.Add(ans[0]), rng.Add(ans[1]), rng.Add(ans[2]);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable( // _Writable(
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
