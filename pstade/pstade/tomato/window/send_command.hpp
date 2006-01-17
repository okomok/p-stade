#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./send_message.hpp"

namespace pstade { namespace tomato {


inline BOOL send_command(HWND hWnd, WORD wID)
{
	ATLASSERT(tomato::is_valid(hWnd));

	return tomato::send_message(hWnd, WM_COMMAND, MAKEWPARAM(wID, 0));
}


} } // namespace pstade::tomato
