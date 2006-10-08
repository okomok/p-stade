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


#include <pstade/oven/atl.hpp> // can be placed first. VC++ ignores, though.


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/tests.hpp>


#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/coll.hpp>
#include <pstade/apple/atl/simpcoll.hpp>
#include <pstade/apple/atl/simpstr.hpp>
#include <pstade/apple/atl/str.hpp>
#include <pstade/apple/atl/cstringt.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test_collection()
{
    int sample[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

#if (_ATL_VER >= 0x0700)

    {
        typedef ATL::CAtlArray<int> rng_t;

        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.Add(i);
        }

        BOOST_CHECK(( oven::test_random_access(rng) ));
    }
    {
        typedef ATL::CAutoPtrArray<int> rng_t;

        rng_t rng; {
            ATL::CAutoPtr<int>
                ptr0(new int(3)), ptr1(new int(1)), ptr2(new int(2)), ptr3(new int(5)),
                ptr4(new int(7)), ptr5(new int(4)), ptr6(new int(6)), ptr7(new int(0));

            rng.Add(ptr0), rng.Add(ptr1), rng.Add(ptr2), rng.Add(ptr3),
            rng.Add(ptr4), rng.Add(ptr5), rng.Add(ptr6), rng.Add(ptr7);
        }

        BOOST_CHECK(( oven::test_random_access(rng) ));
    }
    {
        typedef ATL::CAtlList<int> rng_t;

        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.AddTail(i);
        }

        BOOST_CHECK(( oven::test_bidirectional(rng) ));
    }
    {
        typedef ATL::CAutoPtrList<int> rng_t;

        rng_t rng; {
            ATL::CAutoPtr<int>
                ptr0(new int(3)), ptr1(new int(4)), ptr2(new int(5)), ptr3(new int(4)),
                ptr4(new int(1)), ptr5(new int(2)), ptr6(new int(4)), ptr7(new int(0));

            rng.AddTail(ptr0), rng.AddTail(ptr1), rng.AddTail(ptr2), rng.AddTail(ptr3),
            rng.AddTail(ptr4), rng.AddTail(ptr5), rng.AddTail(ptr6), rng.AddTail(ptr7);
        }

        BOOST_CHECK(( oven::test_bidirectional(rng) ));
    }

#endif // (_ATL_VER >= 0x0700)

#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)
    {
        typedef ATL::CSimpleArray<int> rng_t;

        BOOST_CHECK(( oven::test_Copyable<rng_t>(sample) ));
        rng_t rng = sample|copied;
        BOOST_CHECK(( oven::test_random_access(rng) ));
    }
#else
    {
        typedef ATL::CSimpleArray<int> rng_t;

        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.Add(i);
        }
        BOOST_CHECK(( oven::test_random_access(rng) ));
    }
    {
        typedef ATL::CSimpleValArray<int> rng_t;

        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.Add(i);
        }
        BOOST_CHECK(( oven::test_random_access(rng) ));
    }
#endif
}


void test_string()
{
    std::basic_string<TCHAR> sample(_T("abcdefgh"));

#if (_ATL_VER >= 0x0700)

    {
        typedef ATL::CAtlString rng_t;

        BOOST_CHECK(( oven::test_Copyable<rng_t>(sample) ));
        rng_t rng = sample|copied;
        BOOST_CHECK(( oven::test_random_access(rng) ));
    }
    {
        typedef ATL::CFixedStringT<ATL::CAtlString, 60> rng_t;

        BOOST_CHECK(( oven::test_Copyable<rng_t>(sample) ));
        rng_t rng = sample|copied;
        BOOST_CHECK(( oven::test_random_access(rng) ));
    }

#endif // (_ATL_VER >= 0x0700)

    {
        typedef ATL::CComBSTR rng_t;

        rng_t sample(OLESTR("abcdefg"));
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
