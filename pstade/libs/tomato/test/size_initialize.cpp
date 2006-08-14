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


#include <pstade/tomato/size_initialize.hpp>


#include <pstade/apple/sdk/windows.hpp>


#include <iostream>


void test()
{
    using namespace pstade;
    using namespace tomato;
}


void test_legacy()
{
    using namespace pstade;
    using namespace tomato;

    WNDCLASSEX s;
    s.cbSize = sizeof(MENUITEMINFO);

    std::cout << s.cbClsExtra;
}


void test_modern()
{
    using namespace pstade;
    using namespace tomato;

    WNDCLASSEX s;
    s|size_initialized;

    std::cout << s.cbClsExtra;
}


int test_main(int, char*[])
{
    ::test();
    ::test_legacy();
    ::test_modern();
    return 0;
}
