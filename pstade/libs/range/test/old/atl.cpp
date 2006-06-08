#include <boost/test/minimal.hpp>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_NO_AUTOMATIC_NAMESPACE


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/atl.hpp> // can be placed first


#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range.hpp>


#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/coll.hpp>
#include <pstade/apple/atl/simpcoll.hpp>
#include <pstade/apple/atl/simpstr.hpp>
#include <pstade/apple/atl/str.hpp>
#include <pstade/apple/atl/cstringt.hpp>


namespace boost { namespace microsoft { namespace atl { namespace test {


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



template< class ArrayT >
void init_array(ArrayT& arr)
{
    int // for legacy CSimpleArray
        i0 = 0, i1 = 1, i2 = 2, i3 = 3,
        i4 = 4, i5 = 5, i6 = 6, i7 = 7;

    arr.Add(i3), arr.Add(i1), arr.Add(i2), arr.Add(i5),
    arr.Add(i7), arr.Add(i4), arr.Add(i6), arr.Add(i0);
}


template< class ListT >
void init_list(ListT& lst)
{
    lst.AddTail(3), lst.AddTail(4), lst.AddTail(5), lst.AddTail(4),
    lst.AddTail(1), lst.AddTail(2), lst.AddTail(4), lst.AddTail(0);
}


inline
void collection()
{
    int ans_[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    std::vector<int> ans(boost::begin(ans_), boost::end(ans_));

#if (_ATL_VER >= 0x0700)

    {
        ATL::CAtlArray<int> rng; {
            test::init_array(rng);
        }

        test::random_access(rng, ans);
    }

    {
        ATL::CAutoPtrArray<int> rng; {
            ATL::CAutoPtr<int>
                ptr0(new int(3)), ptr1(new int(1)), ptr2(new int(2)), ptr3(new int(5)),
                ptr4(new int(7)), ptr5(new int(4)), ptr6(new int(6)), ptr7(new int(0));

            rng.Add(ptr0), rng.Add(ptr1), rng.Add(ptr2), rng.Add(ptr3),
            rng.Add(ptr4), rng.Add(ptr5), rng.Add(ptr6), rng.Add(ptr7);
        }

        test::random_access(rng, ans);
    }

    {
        ATL::CAtlList<int> rng; {
            test::init_list(rng);
        }

        test::bidirectional(rng);
    }

    {
        ATL::CAutoPtrList<int> rng; {
            ATL::CAutoPtr<int>
                ptr0(new int(3)), ptr1(new int(4)), ptr2(new int(5)), ptr3(new int(4)),
                ptr4(new int(1)), ptr5(new int(2)), ptr6(new int(4)), ptr7(new int(0));

            rng.AddTail(ptr0), rng.AddTail(ptr1), rng.AddTail(ptr2), rng.AddTail(ptr3),
            rng.AddTail(ptr4), rng.AddTail(ptr5), rng.AddTail(ptr6), rng.AddTail(ptr7);
        }

        test::bidirectional(rng);
    }

    //BOOST_CHECK(false);

#endif // (_ATL_VER >= 0x0700)

    {
        ATL::CSimpleArray<int> rng;
        test::init_array(rng);
        test::random_access(rng, ans);
    }

    {
        ATL::CSimpleValArray<int> rng;
        test::init_array(rng);
        test::random_access(rng, ans);
    }
}


inline
void string()
{
    std::string ans("abcdefgh");

#if (_ATL_VER >= 0x0700)

    {
        ATL::CAtlString rng(_T("abcdefgh"));
        test::random_access(rng, ans);
    }

    {
        ATL::CFixedStringT<ATL::CAtlString, 60> rng(_T("abcdefgh"));
        test::random_access(rng, ans);
    }

    {
        const ATL::CAtlString rng(_T("abcdefgh"));
        boost::begin(rng);
        boost::end(rng);
    }

    {
        const ATL::CFixedStringT<ATL::CAtlString, 60> rng(_T("abcdefgh"));
        boost::begin(rng);
        boost::end(rng);
    }

#endif // (_ATL_VER >= 0x0700)
}


} } } } // namespace boost::microsoft::atl::test


int test_main(int, char*[])
{
    using namespace boost::microsoft::atl;

    test::collection();
    test::string();
    return 0;
}
