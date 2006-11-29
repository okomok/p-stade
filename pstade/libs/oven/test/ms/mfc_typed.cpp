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


#include <pstade/oven/tests.hpp>
#include <pstade/oven/mfc.hpp>


#include <pstade/oven/direct_range.hpp>
#include <pstade/oven/const_lvalue_range.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    { // CTypedPtrArray
        int src[] = { 0,1,2,3,4,5,6,7 };
        std::vector<int *> expected = src|directed|copied;

        CTypedPtrArray<CPtrArray, int *> rng; {
            rng.Add(expected[0]), rng.Add(expected[1]), rng.Add(expected[2]), rng.Add(expected[3]),
            rng.Add(expected[4]), rng.Add(expected[5]), rng.Add(expected[6]), rng.Add(expected[7]);
        }

        BOOST_CHECK( oven::test_SinglePass_Readable(
            rng,
            expected
        ) );

        // 'const_lvalues' removes "Input" from "RandomAccsssInput".
        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|const_lvalues,
            expected
        ) );
    }
    { // CTypedPtrList
        int src[] = { 0,1,2,3,4,5,6,7 };
        std::vector<int *> expected = src|directed|copied;

        CTypedPtrList<CPtrList, int *> rng; {
            rng.AddTail(expected[0]), rng.AddTail(expected[1]), rng.AddTail(expected[2]), rng.AddTail(expected[3]),
            rng.AddTail(expected[4]), rng.AddTail(expected[5]), rng.AddTail(expected[6]), rng.AddTail(expected[7]);
        }

        BOOST_CHECK( oven::test_SinglePass_Readable(
            rng,
            expected
        ) );

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|const_lvalues,
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
