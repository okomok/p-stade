#pragma once

#include "../diagnostic/is_valid.hpp"

namespace pstade { namespace tomato {

// cf. ::IsChild

inline bool is_parent_of(HWND hWndParent, HWND hWndChild)
{
	ATLASSERT(tomato::is_valid(hWndParent));
	ATLASSERT(tomato::is_valid(hWndChild));
	
	return hWndParent == ::GetParent(hWndChild);
}


} } // namespace pstade::tomato
