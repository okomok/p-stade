#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/for_each_child_window.hpp>


#include <algorithm>
#include <iostream>
#include <boost/foreach.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/oven/block.hpp>


bool output(HWND hWnd)
{
    char sz[255];
    ::GetWindowTextA(hWnd, sz, 255);
    if (*sz != '\0')
        std::cout << sz << std::endl;

    return true;
}


struct Output
{
    bool operator()(HWND hWnd) const
    {
        return ::output(hWnd);
    }
};


void pstade_minimal_test()
{
    using namespace pstade;

    gravy::for_each_child_window wnds(::GetDesktopWindow());

    {
        BOOST_FOREACH (gravy::window_ref wnd, oven::block(wnds)) {
            //::output(wnd);
            (void)wnd;
        }
    }

    wnds(&::output);

    {
        gravy::window_ref wnd = ::GetForegroundWindow();
        gravy::for_each_child_window(wnd.handle())(&::output);
    }

    // vexing parse! :-(
    ( gravy::for_each_child_window(::GetDesktopWindow()) ) 
        (&::output);
}
