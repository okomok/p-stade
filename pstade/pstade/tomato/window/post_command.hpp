#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./post_message.hpp"

namespace pstade { namespace tomato {


inline void post_command(HWND hWnd, WORD wID)
{
	ATLASSERT(tomato::is_valid(hWnd));

	tomato::post_message(hWnd, WM_COMMAND, MAKEWPARAM(wID, 0));
}


} } // namespace pstade::tomato
