#pragma once

#include "../diagnostic/is_valid.hpp"

namespace pstade { namespace tomato {


inline bool is_owned(HWND hWnd)
{
	ATLASSERT(tomato::is_valid(hWnd));

	return ::GetWindow(hWnd, GW_OWNER) != NULL;
}


} } // namespace pstade::tomato
