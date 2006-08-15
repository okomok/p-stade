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


#include <pstade/tomato/multibyte_to_widechar.hpp>


#include <string>
#include <pstade/oven/equals.hpp>


void test()
{
    using namespace pstade;
    using namespace tomato;

    std::string s("abcdefg");

    {
        std::wstring ws = tomato::multibyte_to<std::wstring>(s);
        BOOST_CHECK( oven::equals(s, ws) );
    }

    {
        std::wstring ws = s|to_widechar;
        BOOST_CHECK( oven::equals(s, ws) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
