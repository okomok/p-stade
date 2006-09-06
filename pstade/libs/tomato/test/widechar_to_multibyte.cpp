#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/widechar_to_multibyte.hpp>


#include <string>
#include <pstade/oven/equals.hpp>


void test()
{
    using namespace pstade;
    using namespace tomato;

    std::wstring ws(L"abcdefg");

    {
        std::string s = tomato::widechar_to<std::string>(ws);
        BOOST_CHECK( oven::equals(s, ws) );
    }

    {
        std::string s = ws|to_multibyte;
        BOOST_CHECK( oven::equals(s, ws) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
