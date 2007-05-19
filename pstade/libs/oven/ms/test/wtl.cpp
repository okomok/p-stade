#include <pstade/vodka/drink.hpp>

#include <boost/test/minimal.hpp>
#define _WTL_NO_AUTOMATIC_NAMESPACE
#include <pstade/apple/atl/base.hpp>
#include <pstade/apple/wtl/app.hpp>

extern WTL::CAppModule _Module;


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/wtl.hpp>


#include <algorithm>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/apple/wtl/misc.hpp> // CString
#include <pstade/apple/atl/win.hpp>
#include <pstade/apple/wtl/ctrls.hpp>
#include <pstade/apple/wtl/ctrlw.hpp> // CSimpleStack
#include <pstade/oven/tests.hpp>


WTL::CAppModule _Module;


namespace oven = pstade::oven;
using namespace oven;


void test_collection()
{
    int sample[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    {
        typedef WTL::CSimpleStack<int> rng_t;

        std::vector<int> expected = sample|copied;
        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.Add(i);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
}


void test_string()
{
    std::basic_string<TCHAR> sample(_T("abcdefgh"));

    {
        typedef WTL::CString rng_t;
        std::vector<TCHAR> expected = sample|copied;
        BOOST_CHECK(( oven::test_Copyable<rng_t>(sample) ));
        WTL::CString rng = sample|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test_collection();
    ::test_string();
    return 0;
}
