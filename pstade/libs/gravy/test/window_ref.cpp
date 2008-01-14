#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp> // include first for Win32 Boost.Test


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/window_ref.hpp>


namespace gravy = pstade::gravy;
using namespace gravy;


void pstade_minimal_test()
{
    {
        window_ref wnd = ::GetDesktopWindow();
        BOOST_CHECK((HANDLE)wnd == ::GetDesktopWindow());
        BOOST_CHECK(wnd.handle() == ::GetDesktopWindow());
    }
}
