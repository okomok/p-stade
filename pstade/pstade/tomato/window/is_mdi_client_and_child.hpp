#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./is_owned.hpp"
#include "./is_parent_of.hpp"

namespace pstade { namespace tomato {


inline bool is_mdi_client_and_child(HWND hWndMDIClient, HWND hWndChild)
{
	ATLASSERT(tomato::is_valid(hWndMDIClient));
	ATLASSERT(tomato::is_valid(hWndChild));

	return !tomato::is_owned(hWndChild) && tomato::is_parent_of(hWndMDIClient, hWndChild);
}


} } // namespace pstade::tomato
