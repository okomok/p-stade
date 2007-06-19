#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#include <pstade/tomato/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/to_tstring_to.hpp>


#include <string>
#include <pstade/oven/equals.hpp>


void test()
{
    using namespace pstade;

    std::wstring ws(L"abcdefg");

    gravy::tstring ts = ws|tomato::to_tstring;
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
