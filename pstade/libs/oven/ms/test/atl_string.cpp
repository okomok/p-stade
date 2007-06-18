#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_NO_AUTOMATIC_NAMESPACE


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../test/detail/v1_tests.hpp"
#include <pstade/oven/atl.hpp> // can be placed first. VC++ ignores, though.


#include <string>
#include <vector>
#include <boost/range.hpp>


#include <pstade/tomato/atl/config.hpp> // ATL_VER
#include <pstade/tomato/atl/simpstr.hpp>
#include <pstade/tomato/atl/str.hpp>
#include <pstade/tomato/atl/cstringt.hpp>
#include <pstade/oven/as_c_str.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    std::basic_string<TCHAR> sample(_T("abcdefgh"));
    std::vector<TCHAR> expected = sample|copied;

#if (_ATL_VER >= 0x0700)

    {
        typedef ATL::CAtlString rng_t;

        BOOST_CHECK(( oven::test_Copyable<rng_t>(expected) ));
        rng_t rng = sample|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    {
        typedef ATL::CFixedStringT<ATL::CAtlString, 60> rng_t;

        BOOST_CHECK(( oven::test_Copyable<rng_t>(expected) ));
        rng_t rng = sample|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }

#endif // (_ATL_VER >= 0x0700)

    {
        std::vector<OLECHAR> expected = OLESTR("abcdefgh")|as_c_str|copied;

        typedef ATL::CComBSTR rng_t;

        rng_t rng(OLESTR("abcdefgh"));
        // CComBSTR overloads operator&..., so,
        // strictly speaking, he seems not 'CopyConstructible'.
        BOOST_CHECK(( oven::test_Copyable<rng_t>(expected) ));
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
