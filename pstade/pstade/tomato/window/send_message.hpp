#pragma once

#include "../diagnostic/is_valid.hpp"

namespace pstade { namespace tomato {


inline LRESULT send_message(HWND hWnd, UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
{
	ATLASSERT(tomato::is_valid(hWnd));

	return ::SendMessage(hWnd, message, wParam, lParam);
}


} } // namespace pstade::tomato
