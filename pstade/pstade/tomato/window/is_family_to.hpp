#pragma once

#include "../diagnostic/is_valid.hpp"

namespace pstade { namespace tomato {


inline bool is_family_to(HWND hWnd0, HWND hWnd1)
{
	ATLASSERT(tomato::is_valid(hWnd0));
	ATLASSERT(tomato::is_valid(hWnd1));

	if (hWnd0 == hWnd1)
		return true;

	ATL::CWindow wnd0(hWnd0);
	ATL::CWindow wnd1(hWnd1);

	return wnd0.GetTopLevelParent() == wnd1.GetTopLevelParent();
}


} } // namespace pstade::tomato
