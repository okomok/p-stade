#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/tstring.hpp>


#include <string>
#include <pstade/oven/equals.hpp>


void test()
{
    using namespace pstade;
    using namespace tomato;

    std::wstring ws(L"abcdefg");

    tstring ts = ws|to_tstring;
    BOOST_CHECK( oven::equals(ts, ws) );

    {
        std::wstring ws_ = tomato::tstring_to<std::wstring>(ts);
        BOOST_CHECK( oven::equals(ws, ws_) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
