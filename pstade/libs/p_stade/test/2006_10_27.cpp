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
//#include <pstade/oven/atl.hpp> // can be placed first. VC++ ignores, though.


#include <string>
#include <vector>
#include <boost/range.hpp>


#include <pstade/tomato/atl/config.hpp> // ATL_VER
#include <pstade/tomato/atl/coll.hpp>
#include <pstade/tomato/atl/simpcoll.hpp>
#include <pstade/tomato/atl/simpstr.hpp>
#include <pstade/tomato/atl/str.hpp>
#include <pstade/tomato/atl/cstringt.hpp>


#include <boost/algorithm/string.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{

#if (_ATL_VER >= 0x0700)

    typedef std::basic_string<TCHAR> value_type;

    std::vector<value_type> splitVec;

    ATL::CString csText(_T("ab,cde,fg,h"));
    TCHAR const *psz = csText.GetString();
    boost::split( splitVec, psz, boost::is_any_of(_T(",")) );

    std::vector<value_type> expected; {
        expected.push_back(value_type(_T("ab")));
        expected.push_back(value_type(_T("cde")));
        expected.push_back(value_type(_T("fg")));
        expected.push_back(value_type(_T("h")));
    }
    
    BOOST_CHECK( oven::equals(splitVec, expected) );

#endif // (_ATL_VER >= 0x0700)

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
