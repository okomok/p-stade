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


#include <pstade/tomato/size_initialize.hpp>


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/used.hpp>


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
    pstade::used(s);
}


void test_modern()
{
    using namespace pstade;
    using namespace tomato;

    WNDCLASSEX s;
    s|size_initialized;
    pstade::used(s);
}


int test_main(int, char*[])
{
    ::test();
    ::test_legacy();
    ::test_modern();
    return 0;
}
