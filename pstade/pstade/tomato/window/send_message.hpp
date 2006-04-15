#ifndef PSTADE_TOMATO_WINDOW_SEND_COMMAND_HPP
#define PSTADE_TOMATO_WINDOW_SEND_COMMAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
LRESULT send_message(HWND hWnd, UINT msg, WPARAM wParam = 0, LPARAM lParam = 0)
{
	BOOST_ASSERT(diet::valid(hWnd));

	return ::SendMessage(hWnd, msg, wParam, lParam);
}


} } // namespace pstade::tomato


#endif
