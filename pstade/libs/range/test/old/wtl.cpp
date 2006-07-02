#include <boost/test/minimal.hpp>
#define _WTL_NO_AUTOMATIC_NAMESPACE
#include <atlbase.h>
#include <atlapp.h>

extern WTL::CAppModule _Module;


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/wtl.hpp>


#include <algorithm>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <atlmisc.h>  // CString
#include <atlwin.h>
#include <atlctrls.h>
#include <atlctrlw.h> // CSimpleStack
#include <pstade/oven/distance.hpp>


WTL::CAppModule _Module;


namespace boost { namespace microsoft { namespace wtl { namespace test {


template< class Range1, class Range2 >
bool equals(Range1& rng1, Range2& rng2)
{
    return
        std::equal(boost::begin(rng1), boost::end(rng1), boost::begin(rng2)) &&
        pstade::oven::distance(rng1) == pstade::oven::distance(rng2)
    ;
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


inline
void collection()
{
    int ans_[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    std::vector<int> ans(boost::begin(ans_), boost::end(ans_));

    {
        WTL::CSimpleStack<int> rng;
        test::init_array(rng);
        test::random_access(rng, ans);
    }
}


inline
void string_()
{
    std::string ans("abcdefgh");

    {
        WTL::CString rng(_T("abcdefgh"));
        test::random_access(rng, ans);
    }

    {
        WTL::CString rng;
        test::random_access(rng, std::string());
    }
}


} } } } // namespace boost::microsoft::wtl::test


int test_main(int, char*[])
{
    using namespace boost::microsoft::wtl;
    
    test::collection();
    test::string_();
    return 0;
}
