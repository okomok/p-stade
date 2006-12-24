#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/window/for_each_child_window.hpp>
#include <pstade/sausage/yield_range.hpp>


#include <algorithm>
#include <iostream>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven.hpp>


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


void test()
{
    using namespace pstade;
    using namespace sausage;

    tomato::for_each_child_window wnds(::GetDesktopWindow());

    {
        BOOST_FOREACH (tomato::window_ref wnd, wnds|yielded) {
            //::output(wnd);
            (void)wnd;
        }
    }

    wnds(&::output);


    {
        tomato::window_ref wnd = ::GetForegroundWindow();
        tomato::for_each_child_window(wnd.handle())(::output);
    }

    // vexing parse! :-(
    ( tomato::for_each_child_window(::GetDesktopWindow()) ) 
        (&::output);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
