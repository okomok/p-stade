#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/class_name.hpp>


#include <pstade/oven/copy_range.hpp>
#include <pstade/gravy/tstring.hpp>
#include <pstade/gravy/tiostream.hpp>
#include <pstade/gravy/c_str.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/equals.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    namespace gravy = pstade::gravy;
    using namespace gravy;

    HWND hWnd = ::GetForegroundWindow();

    {
        class_name text(hWnd);
        tstring str = text|oven::copied;
        tcout << str << std::endl;
    }

    {
        class_name text(hWnd);
        BOOST_CHECK( oven::equals(c_str(text)|oven::as_c_str, text) );
    }
}
