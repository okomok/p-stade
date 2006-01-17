#pragma once

#include <atlgdi.h>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "./get_write_logfont.hpp"

namespace pstade { namespace tomato {


template< class StringT, class Profile >
void profile_write_font(Profile& pr, HWND hWnd, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWnd));

	HFONT hFont = ATL::CWindow(hWnd).GetFont();
	if (hFont == NULL)
		return;

	tomato::profile_write_logfont(pr, WTL::CLogFont(hFont), prefix);
}


// DEPRECATED
template< class StringT, class Profile >
bool profile_get_font(Profile& pr, HWND hWnd, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWnd));

	LOGFONT lf;
	if (!tomato::profile_get_logfont(pr, lf, prefix))
		return false;

	HFONT hFont = ::CreateFontIndirect(&lf);
	tomato::api_verify(hFont != NULL);

	ATL::CWindow(hWnd).SetFont(hFont);

	return true;
}


} } // namespace pstade::tomato
