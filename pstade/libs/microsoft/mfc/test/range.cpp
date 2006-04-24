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

#include <algorithm>
#include <string>
#include <boost/range.hpp>

#include <afxcoll.h>
#if (_MFC_VER >= 0x0700)
    #include <afxstr.h>
#endif
#include <afxtempl.h>

#include <boost/test/minimal.hpp>
#include <boost/microsoft/mfc/range.hpp>


namespace boost { namespace microsoft { namespace mfc { namespace test {


template< class Range1, class Range2 >
bool equals(Range1& rng1, Range2& rng2)
{
    return
        std::equal(boost::begin(rng1), boost::end(rng1), boost::begin(rng2)) &&
        boost::size(rng1) == boost::size(rng2)
    ;
}


template< class Range1, class Range2 >
void random_access(Range1& rng, const Range2& ans)
{
    std::random_shuffle(boost::begin(rng), boost::end(rng));
    std::sort(boost::begin(rng), boost::end(rng));
    BOOST_CHECK( test::equals(rng, ans) );

    std::random_shuffle(boost::begin(rng), boost::end(rng));
    std::stable_sort(boost::begin(rng), boost::end(rng));
    BOOST_CHECK( test::equals(rng, ans) );

    std::random_shuffle(boost::begin(rng), boost::end(rng));
    std::partial_sort(boost::begin(rng), boost::end(rng), boost::end(rng));
    BOOST_CHECK( test::equals(rng, ans) );
}


template< class Range >
void bidirectional(Range& rng)
{
    BOOST_CHECK( boost::size(rng) == std::distance(boost::begin(rng), boost::end(rng)) );
}


inline
void collection()
{
    {
        int ans[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        CArray<int, const int&> rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        test::random_access(rng, ans);
    }
    {
        BYTE ans[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        CByteArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        test::random_access(rng, ans);
    }

    {
        DWORD ans[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        CDWordArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        test::random_access(rng, ans);
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

        test::random_access(rng, ans);
    }

    {
        UINT ans[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        CUIntArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        test::random_access(rng, ans);
    }

    {
        WORD ans[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        CWordArray rng; {
            rng.Add(0), rng.Add(1), rng.Add(2), rng.Add(3),
            rng.Add(4), rng.Add(5), rng.Add(6), rng.Add(7);
        }

        test::random_access(rng, ans);
    }


    {
        int ans[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
        CList<int, const int&> rng; {
            rng.AddTail(0), rng.AddTail(1), rng.AddTail(2), rng.AddTail(3),
            rng.AddTail(4), rng.AddTail(5), rng.AddTail(6), rng.AddTail(7);
        }

        test::bidirectional(rng);
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

        test::bidirectional(rng);
    }
}


inline
void string_()
{
    std::string ans("abcdefgh");

    {
        CString rng(_T("abcdefgh"));
        test::random_access(rng, ans);
    }

    {
        CString rng;
        test::random_access(rng, std::string());
    }
}


} } } } // namespace boost::microsoft::mfc::test


int test_main(int, char*[])
{
    using namespace boost::microsoft::mfc;

    test::collection();
    test::string_();
    return 0;
}
