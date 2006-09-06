#ifndef PSTADE_TOMATO_WINDOW_POST_MESSAGE_HPP
#define PSTADE_TOMATO_WINDOW_POST_MESSAGE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
void post_message(window_ref wnd,
    UINT msg, WPARAM wParam = 0, LPARAM lParam = 0)
{
    PSTADE_REQUIRE(::PostMessage(wnd, msg, wParam, lParam));
}


} } // namespace pstade::tomato


#endif
