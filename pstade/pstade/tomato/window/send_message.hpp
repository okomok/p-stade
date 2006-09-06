#ifndef PSTADE_TOMATO_WINDOW_SEND_COMMAND_HPP
#define PSTADE_TOMATO_WINDOW_SEND_COMMAND_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
LRESULT send_message(window_ref wnd,
    UINT msg, WPARAM wParam = 0, LPARAM lParam = 0)
{
    return ::SendMessage(wnd, msg, wParam, lParam);
}


} } // namespace pstade::tomato


#endif
