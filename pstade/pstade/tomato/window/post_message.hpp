#ifndef PSTADE_TOMATO_WINDOW_POST_MESSAGE_HPP
#define PSTADE_TOMATO_WINDOW_POST_MESSAGE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
void post_message(HWND hWnd, UINT msg, WPARAM wParam = 0, LPARAM lParam = 0)
{
    BOOST_ASSERT(diet::valid(hWnd));
    PSTADE_REQUIRE(::PostMessage(hWnd, msg, wParam, lParam));
}


} } // namespace pstade::tomato


#endif
