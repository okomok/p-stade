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


#include <pstade/oven/tests.hpp>
#include <pstade/oven/atl.hpp> // can be placed first. VC++ ignores, though.


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/transform_range.hpp>
#include <pstade/oven/const_lvalue_range.hpp>


#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/coll.hpp>
#include <pstade/apple/atl/simpcoll.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    int sample[] = { 3,1,2,5,7,4,6,0 };
    std::vector<int> expected = sample|copied;

#if (_ATL_VER >= 0x0700)

    {
        typedef ATL::CAtlArray<int> rng_t;

        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.Add(i);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
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

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    {
        typedef ATL::CComQIPtr<IDispatch> quiPtr_t;
        typedef ATL::CAdapt<quiPtr_t> adapted_t;
        adapted_t sample[] = {
            adapted_t(), adapted_t(), adapted_t(), adapted_t(),
            adapted_t(), adapted_t(), adapted_t(), adapted_t()
        };
        std::vector<adapted_t> expected = sample|copied;

        typedef ATL::CInterfaceArray<IDispatch> rng_t;

        rng_t rng; {
            quiPtr_t
                ptr0, ptr1, ptr2, ptr3,
                ptr4, ptr5, ptr6, ptr7;

            rng.Add(ptr0), rng.Add(ptr1), rng.Add(ptr2), rng.Add(ptr3),
            rng.Add(ptr4), rng.Add(ptr5), rng.Add(ptr6), rng.Add(ptr7);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|transformed(make_CAdapt)|const_lvalues,
            expected
        ) );
    }

#endif // (_ATL_VER >= 0x0700)

#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)
    {
        typedef ATL::CSimpleArray<int> rng_t;

        BOOST_CHECK(( oven::test_Copyable<rng_t>(sample) ));
        rng_t rng = sample|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
#else
    {
        typedef ATL::CSimpleArray<int> rng_t;

        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.Add(i);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
    {
        typedef ATL::CSimpleValArray<int> rng_t;

        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.Add(i);
        }

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng,
            expected
        ) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
