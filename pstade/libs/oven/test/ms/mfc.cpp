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
#if (_MFC_VER >= 0x0700)
    #include <afxstr.h>
#endif
#include <afxtempl.h>

#include <boost/test/minimal.hpp>
#include <pstade/oven/mfc.hpp>


#include <pstade/oven/tests.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test_collection()
{
    {
        CArray<int, const int&> rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK(( oven::test_random_access(rng) ));
    }
    {
        CByteArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK(( oven::test_random_access(rng) ));
    }

    {
        CDWordArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK(( oven::test_random_access(rng) ));
    }

    {
        CString ans[] = {
            CString(_T('0')), CString(_T('1')), CString(_T('2')), CString(_T('3')),
            CString(_T('4')), CString(_T('5')), CString(_T('6')), CString(_T('7'))
        };

        CStringArray rng; {
            rng.Add(ans[0]), rng.Add(ans[1]), rng.Add(ans[2]), rng.Add(ans[3]),
            rng.Add(ans[4]), rng.Add(ans[5]), rng.Add(ans[6]), rng.Add(ans[7]);
        }

        BOOST_CHECK(( oven::test_random_access(rng) ));
    }

    {
        CUIntArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK(( oven::test_random_access(rng) ));
    }

    {
        CWordArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        BOOST_CHECK(( oven::test_random_access(rng) ));
    }


    {
        CList<int, const int&> rng; {
            rng.AddTail(0), rng.AddTail(1), rng.AddTail(2), rng.AddTail(3),
            rng.AddTail(4), rng.AddTail(5), rng.AddTail(6), rng.AddTail(7);
        }

        BOOST_CHECK(( oven::test_bidirectional(rng) ));
    }

    {
        CString ans[] = {
            CString(_T('0')), CString(_T('1')), CString(_T('2')), CString(_T('3')),
            CString(_T('4')), CString(_T('5')), CString(_T('6')), CString(_T('7'))
        };

        CStringList rng; {
            rng.AddTail(ans[0]), rng.AddTail(ans[1]), rng.AddTail(ans[2]), rng.AddTail(ans[3]),
            rng.AddTail(ans[4]), rng.AddTail(ans[5]), rng.AddTail(ans[6]), rng.AddTail(ans[7]);
        }

        BOOST_CHECK(( oven::test_bidirectional(rng) ));
    }
}


void test_string()
{
    std::basic_string<TCHAR> sample(_T("abcdefgh"));

    {
        typedef ::CString rng_t;

        BOOST_CHECK(( oven::test_Copyable<rng_t>(sample) ));
        rng_t rng = sample|copied;
        BOOST_CHECK(( oven::test_random_access(rng) ));
    }
}


int test_main(int, char*[])
{
    ::test_collection();
    ::test_string();
    return 0;
}
