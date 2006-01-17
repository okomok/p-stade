#pragma once

#if !defined(_WIN32_WCE)

#include "../cast/boolean_cast.hpp"
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../structure/version_initialize.hpp"
#include "./get_write_window_placement.hpp"

namespace pstade { namespace tomato {


template< class StringT, class Profile >
void profile_write_placement(Profile& pr, HWND hWnd, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWnd));

	WINDOWPLACEMENT wndpl;
	tomato::version_initialize(wndpl);
	tomato::api_verify(::GetWindowPlacement(hWnd, &wndpl));

	tomato::profile_write_window_placement(pr, wndpl, prefix);
}


template< class StringT, class Profile >
bool profile_get_placement(Profile& pr, HWND hWnd, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWnd));

	WINDOWPLACEMENT wndpl;
	tomato::version_initialize(wndpl);

	if (!tomato::profile_get_window_placement(pr, wndpl, prefix))
		return false; // not found

	tomato::api_verify(::SetWindowPlacement(hWnd, &wndpl));
	return true;
}


// showCmd service
template< class StringT, class Profile >
void profile_get_placement(Profile& pr, HWND hWnd, int showCmd, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWnd));

	if (!tomato::profile_get_placement(pr, hWnd, prefix)) // not found
		::ShowWindow(hWnd, showCmd);
}


// give a chance
template< class StringT, class Profile, class Functor >
void profile_get_placement_intrusive(Profile& pr, HWND hWnd, int showCmd, Functor fun, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWnd));

	WINDOWPLACEMENT wndpl;
	tomato::version_initialize(wndpl);

	if (tomato::profile_get_window_placement(pr, wndpl, prefix)) {
		showCmd = wndpl.showCmd; // show it later
		wndpl.showCmd = SW_HIDE;
		tomato::api_verify(::SetWindowPlacement(hWnd, &wndpl));
	}

	fun();
	::ShowWindow(hWnd, showCmd);
}


} } // namespace pstade::tomato

#endif // !defined(_WIN32_WCE)
