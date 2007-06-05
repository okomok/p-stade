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
#include <pstade/oven/transformed.hpp>
#include <pstade/oven/const_refs.hpp>


#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/coll.hpp>
#include <pstade/apple/atl/simpcoll.hpp>
#include <pstade/apple/atl/simpstr.hpp>
#include <pstade/apple/atl/str.hpp>
#include <pstade/apple/atl/cstringt.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
#if (_ATL_VER >= 0x0700)

    int sample[] = { 3,1,2,5,7,4,6,0 };
    std::vector<int> expected = sample|copied;

    {
        typedef ATL::CAtlList<int> rng_t;

        rng_t rng;
        BOOST_FOREACH (int i, sample) {
            rng.AddTail(i);
        }

        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
            rng,
            expected
        ) );
    }
    {
        typedef ATL::CAutoPtrList<int> rng_t;

        rng_t rng; {
            ATL::CAutoPtr<int>
                ptr0(new int(3)), ptr1(new int(1)), ptr2(new int(2)), ptr3(new int(5)),
                ptr4(new int(7)), ptr5(new int(4)), ptr6(new int(6)), ptr7(new int(0));

            rng.AddTail(ptr0), rng.AddTail(ptr1), rng.AddTail(ptr2), rng.AddTail(ptr3),
            rng.AddTail(ptr4), rng.AddTail(ptr5), rng.AddTail(ptr6), rng.AddTail(ptr7);
        }

        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
            rng,
            expected
        ) );
    }
    {
        typedef ATL::CHeapPtrList<int> rng_t;

        rng_t rng; {
            ATL::CHeapPtr<int> ptr0; ptr0.Allocate(1); *ptr0 = 3;
            ATL::CHeapPtr<int> ptr1; ptr1.Allocate(1); *ptr1 = 1;
            ATL::CHeapPtr<int> ptr2; ptr2.Allocate(1); *ptr2 = 2;
            ATL::CHeapPtr<int> ptr3; ptr3.Allocate(1); *ptr3 = 5;
            ATL::CHeapPtr<int> ptr4; ptr4.Allocate(1); *ptr4 = 7;
            ATL::CHeapPtr<int> ptr5; ptr5.Allocate(1); *ptr5 = 4;
            ATL::CHeapPtr<int> ptr6; ptr6.Allocate(1); *ptr6 = 6;
            ATL::CHeapPtr<int> ptr7; ptr7.Allocate(1); *ptr7 = 0;

            rng.AddTail(ptr0), rng.AddTail(ptr1), rng.AddTail(ptr2), rng.AddTail(ptr3),
            rng.AddTail(ptr4), rng.AddTail(ptr5), rng.AddTail(ptr6), rng.AddTail(ptr7);
        }

        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
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

        typedef ATL::CInterfaceList<IDispatch> rng_t;

        rng_t rng; {
            quiPtr_t
                ptr0, ptr1, ptr2, ptr3,
                ptr4, ptr5, ptr6, ptr7;

            rng.AddTail(ptr0), rng.AddTail(ptr1), rng.AddTail(ptr2), rng.AddTail(ptr3),
            rng.AddTail(ptr4), rng.AddTail(ptr5), rng.AddTail(ptr6), rng.AddTail(ptr7);
        }

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|transformed(make_CAdapt)|const_refs,
            expected
        ) );
    }

#endif // (_ATL_VER >= 0x0700)
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
