#ifndef PSTADE_TOMATO_WINDOW_SEND_COMMAND_HPP
#define PSTADE_TOMATO_WINDOW_SEND_COMMAND_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"
#include "./send_message.hpp"


namespace pstade { namespace tomato {


inline
bool send_command(HWND hWnd, WORD wID)
{
	BOOST_ASSERT(diet::valid(hWnd));

	return tomato::send_message(hWnd, WM_COMMAND, MAKEWPARAM(wID, 0));
}


} } // namespace pstade::tomato


#endif
