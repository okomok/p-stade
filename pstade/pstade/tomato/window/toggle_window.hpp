#pragma once

#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


// Note: Return-value means visibility.
inline BOOL toggle_window(HWND hWnd) // throw()
{
	ATLASSERT(tomato::is_valid(hWnd));

	BOOL bVisible = !::IsWindowVisible(hWnd);
	::ShowWindow(hWnd, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	return bVisible;
}


} } // namespace pstade::tomato
