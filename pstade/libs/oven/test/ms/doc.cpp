#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#define _WIN32_WINNT 0x0400 // for <boost/test/minimal.hpp>
#define _AFXDLL


#include <pstade/apple/mfc/afx.hpp> // must be included first.


#include <boost/test/minimal.hpp>


#include <vector>
#include <pstade/apple/atl/simpcoll.hpp>
#include <pstade/apple/mfc/afxtempl.hpp>
#include <pstade/apple/wtl/app.hpp>
#include <pstade/apple/wtl/misc.hpp>


#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/lexical_cast.hpp> // thanks to cryolite
#include <pstade/oven/atl.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/mfc.hpp>
#include <pstade/oven/ranges.hpp>
#include <pstade/oven/wtl.hpp>
#include <pstade/lambda_result.hpp> // thanks to uskz


void test()
{
    using namespace pstade;
    namespace lambda = boost::lambda;

    ATL::CSimpleValArray<int> arr;
        arr.Add(5), arr.Add(2), arr.Add(3), arr.Add(5)
    ;

    ::CList<int, int const&> lst;
        lst.AddTail(4), lst.AddTail(6), lst.AddTail(4), lst.AddTail(1)
    ;

    std::vector<int> vec =
        WTL::CString(_T("9876")) |
            oven::transformed(lambda::bind(op_lexical_cast<int>(), lambda::_1)) |
            oven::copied
    ;

    BOOST_CHECK( oven::equals(
        boost::tie(arr, lst) |
            oven::zipped_with(lambda::_1 + lambda::_2)
        ,
        vec
    ) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
