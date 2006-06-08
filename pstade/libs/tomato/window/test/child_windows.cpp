#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/window/child_windows.hpp>
#include <pstade/sausage.hpp>


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

    tomato::child_windows wnds(::GetDesktopWindow());

    {
        sausage::enumerate(wnds, Output());
    }

    {
        BOOST_FOREACH (HWND hWnd, wnds|sausage::enumerated) {
            ::output(hWnd);
        }
    }

    {
        // RangeもEnumerable
        // (ただし、メンバ関数を使ってカスタマイズしたRangeのみ)
        std::string str("abcde");
        BOOST_FOREACH (char ch, str|sausage::enumerated) {
            std::cout << ch;
        }
    }

    {
        // むちゃをしてみる (24個のスレッド)
        BOOST_FOREACH (
            HWND hWnd,
            wnds|
                sausage::enumerated|sausage::enumerated|sausage::enumerated|sausage::enumerated|
                sausage::enumerated|sausage::enumerated|sausage::enumerated|sausage::enumerated|
                sausage::enumerated|sausage::enumerated|sausage::enumerated|sausage::enumerated|
                sausage::enumerated|sausage::enumerated|sausage::enumerated|sausage::enumerated|
                sausage::enumerated|sausage::enumerated|sausage::enumerated|sausage::enumerated|
                sausage::enumerated|sausage::enumerated|sausage::enumerated|sausage::enumerated
        ) {
            ::output(hWnd);
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
