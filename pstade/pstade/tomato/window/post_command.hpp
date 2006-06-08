#ifndef PSTADE_TOMATO_WINDOW_POST_COMMAND_HPP
#define PSTADE_TOMATO_WINDOW_POST_COMMAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include "../diet/valid.hpp"
#include "./post_message.hpp"


namespace pstade { namespace tomato {


inline
void post_command(HWND hWnd, WORD wID)
{
    BOOST_ASSERT(diet::valid(hWnd));

    tomato::post_message(hWnd, WM_COMMAND, MAKEWPARAM(wID, 0));
}


} } // namespace pstade::tomato


#endif
