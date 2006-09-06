#ifndef PSTADE_TOMATO_WINDOW_SEND_COMMAND_HPP
#define PSTADE_TOMATO_WINDOW_SEND_COMMAND_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include "./send_message.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
bool send_command(window_ref wnd, WORD wID)
{
    return tomato::send_message(wnd, WM_COMMAND, MAKEWPARAM(wID, 0));
}


} } // namespace pstade::tomato


#endif
