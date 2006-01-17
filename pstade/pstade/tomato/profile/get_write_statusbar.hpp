#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./query_dword.hpp"
#include "./set_dword.hpp"

namespace pstade { namespace tomato {


template< class StringT, class Profile > inline
void profile_write_statusbar(Profile& pr, HWND hWndStatusBar, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWndStatusBar));

	tomato::profile_set_dword(pr, prefix + _T("statusbar.visible"), ::IsWindowVisible(hWndStatusBar) ? 1 : 0);
}


template< class StringT, class Profile >
bool profile_get_statusbar(Profile& pr, HWND hWndStatusBar, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWndStatusBar));

	DWORD dwValue;
	if (!tomato::profile_query_dword(pr, prefix + _T("statusbar.visible"), dwValue))
		return false; // not found

	::ShowWindow(hWndStatusBar, dwValue == 1 ? SW_SHOWNOACTIVATE : SW_HIDE);
	return true;
}


} } // namespace pstade::tomato
