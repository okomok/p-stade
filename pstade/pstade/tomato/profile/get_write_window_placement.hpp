#pragma once

#if !defined(_WIN32_WCE)


#include "./query_dword.hpp"
#include "./set_dword.hpp"

namespace pstade { namespace tomato {


template< class StringT, class Profile >
void profile_write_window_placement(Profile& pr, const WINDOWPLACEMENT& wndpl, const StringT& prefix)
{
	tomato::profile_set_dword(pr, prefix + _T("placement.flags"), wndpl.flags);
	tomato::profile_set_dword(pr, prefix + _T("placement.showCmd"), wndpl.showCmd);
	tomato::profile_set_dword(pr, prefix + _T("placement.ptMinPosition.x"), wndpl.ptMinPosition.x);
	tomato::profile_set_dword(pr, prefix + _T("placement.ptMinPosition.y"), wndpl.ptMinPosition.y);
	tomato::profile_set_dword(pr, prefix + _T("placement.ptMaxPosition.x"), wndpl.ptMaxPosition.x);
	tomato::profile_set_dword(pr, prefix + _T("placement.ptMaxPosition.y"), wndpl.ptMaxPosition.y);
	tomato::profile_set_dword(pr, prefix + _T("placement.rcNormalPosition.left"), wndpl.rcNormalPosition.left);
	tomato::profile_set_dword(pr, prefix + _T("placement.rcNormalPosition.top"), wndpl.rcNormalPosition.top);
	tomato::profile_set_dword(pr, prefix + _T("placement.rcNormalPosition.right"), wndpl.rcNormalPosition.right);
	tomato::profile_set_dword(pr, prefix + _T("placement.rcNormalPosition.bottom"), wndpl.rcNormalPosition.bottom);
}


template< class StringT, class Profile >
bool profile_get_window_placement(Profile& pr, WINDOWPLACEMENT& wndpl, const StringT& prefix)
{
	DWORD
		dwFlags = 0, dwShowCmd = 0,
		dwMinX = 0, dwMinY = 0,
		dwMaxX = 0, dwMaxY = 0,
		dwLeft = 0, dwTop = 0, dwRight = 0, dwBottom = 0
	;

	if (
		tomato::profile_query_dword(pr, prefix + _T("placement.flags"), dwFlags) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.showCmd"), dwShowCmd) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.ptMinPosition.x"), dwMinX) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.ptMinPosition.y"), dwMinY) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.ptMaxPosition.x"), dwMaxX) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.ptMaxPosition.y"), dwMaxY) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.rcNormalPosition.left"), dwLeft) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.rcNormalPosition.top"), dwTop) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.rcNormalPosition.right"), dwRight) &&
		tomato::profile_query_dword(pr, prefix + _T("placement.rcNormalPosition.bottom"), dwBottom)
	)
	{
		wndpl.flags = dwFlags;
		wndpl.showCmd = dwShowCmd;
		wndpl.ptMinPosition.x = dwMinX;
		wndpl.ptMinPosition.y = dwMinY;
		wndpl.ptMaxPosition.x = dwMaxX;
		wndpl.ptMaxPosition.y = dwMaxY;
		wndpl.rcNormalPosition.left = dwLeft;
		wndpl.rcNormalPosition.top = dwTop;
		wndpl.rcNormalPosition.right = dwRight;
		wndpl.rcNormalPosition.bottom = dwBottom;
		return true;
	}

	return false;
}


} } // namespace pstade::tomato


#endif // !defined(_WIN32_WCE)
