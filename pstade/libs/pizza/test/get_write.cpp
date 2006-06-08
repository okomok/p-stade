#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pizza/string.hpp>
#include <pstade/pizza/ini_section.hpp>
#include <pstade/pizza/reg_key.hpp>
#include <pstade/pizza/initialize.hpp>
#include <pstade/pizza/set_string.hpp>
#include <pstade/pizza/set_integer.hpp>
#include <pstade/pizza/integer.hpp>
#include <pstade/pizza/string.hpp>
#include <pstade/pizza/get_write/font.hpp>
#include <pstade/pizza/get_write/placement.hpp>


#include <vector>
#include <string>
#include <sstream>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


template< class Profile >
void test_profile(Profile& pr)
{
    using namespace pstade;

    pizza::initialize(pr, "MyFont");

    HWND hWnd = ::GetDesktopWindow();

    {   
        pizza::write_font(pr, hWnd);
        pizza::write_placement(pr, hWnd);
    }

}


void test_ini_section()
{
    using namespace pstade;

    pizza::ini_section sec;
    ::test_profile(sec);
}


void test_reg_key()
{
    using namespace pstade;

    ATL::CRegKey key;
    ::test_profile(key);
}


int test_main(int, char*[])
{
    ::test_ini_section();
    ::test_reg_key();
    return 0;
}
