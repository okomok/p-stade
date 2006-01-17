#pragma once

#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


inline void post_message(HWND hWnd, UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
{
	ATLASSERT(tomato::is_valid(hWnd));

	tomato::api_verify(::PostMessage(hWnd, message, wParam, lParam));
}


} } // namespace pstade::tomato
