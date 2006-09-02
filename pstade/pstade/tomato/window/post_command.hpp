#ifndef PSTADE_TOMATO_WINDOW_POST_COMMAND_HPP
#define PSTADE_TOMATO_WINDOW_POST_COMMAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include "../make.hpp"
#include "./post_message.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
void post_command(window_ref wnd, WORD wID)
{
    tomato::post_message(wnd, WM_COMMAND, tomato::make_WPARAM(wID, 0));
}


} } // namespace pstade::tomato


#endif
