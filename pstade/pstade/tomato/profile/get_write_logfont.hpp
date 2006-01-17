#pragma once

#include <boost/array.hpp>
#include <boost/mpl/long.hpp>
#include <pstade/integral_cast.hpp>
#include "../gdi/decipoint_font_height.hpp"
#include "../gdi/font_height_from_decipoint.hpp"
#include "../structure/zero_initialize.hpp"
#include "./query_dword.hpp"
#include "./query_string.hpp"
#include "./set_dword.hpp"
#include "./set_string.hpp"

namespace pstade { namespace tomato {


template< class StringT, class Profile >
void profile_write_logfont(Profile& pr, const LOGFONT& lf, const StringT& prefix, HDC hDC = NULL)
{
	tomato::profile_set_string(pr, prefix + _T("logFont.lfFaceName"), lf.lfFaceName);
	tomato::profile_set_dword(pr, prefix + _T("logFont.decipointHeight"), tomato::decipoint_font_height(lf.lfHeight, hDC));
	tomato::profile_set_dword(pr, prefix + _T("logFont.lfWeight"), lf.lfWeight);
	tomato::profile_set_dword(pr, prefix + _T("logFont.lfItalic"), lf.lfItalic);
	tomato::profile_set_dword(pr, prefix + _T("logFont.lfUnderLine"), lf.lfUnderline);
	tomato::profile_set_dword(pr, prefix + _T("logFont.lfStrikeOut"), lf.lfStrikeOut);
	tomato::profile_set_dword(pr, prefix + _T("logFont.lfCharSet"), lf.lfCharSet);
}


template< class StringT, class Profile >
bool profile_get_logfont(Profile& pr, LOGFONT& lf, const StringT& prefix, HDC hDC = NULL)
{
	tomato::zero_initialize(lf);

	// Workaround: Boost.Range doesn't support built-in array of char.
	boost::array<TCHAR, LF_FACESIZE> szFaceName;

	DWORD
		dwDecipointHeight = 0, dwWeight = 0, dwItalic = 0,
		dwUnderline = 0, dwStrikeOut = 0, dwCharSet = 0
	;

	if (
		tomato::profile_query_string(pr, prefix + _T("logFont.lfFaceName"), szFaceName) &&
		tomato::profile_query_dword(pr, prefix + _T("logFont.decipointHeight"), dwDecipointHeight) &&
		tomato::profile_query_dword(pr, prefix + _T("logFont.lfWeight"), dwWeight) &&
		tomato::profile_query_dword(pr, prefix + _T("logFont.lfItalic"), dwItalic) &&
		tomato::profile_query_dword(pr, prefix + _T("logFont.lfUnderLine"), dwUnderline) &&
		tomato::profile_query_dword(pr, prefix + _T("logFont.lfStrikeOut"), dwStrikeOut) &&
		tomato::profile_query_dword(pr, prefix + _T("logFont.lfCharSet"), dwCharSet)
	)
	{
		lstrcpy(lf.lfFaceName, boost::const_begin(szFaceName));
		lf.lfHeight = tomato::font_height_from_decipoint(dwDecipointHeight, hDC);
		lf.lfWeight = dwWeight;
		lf.lfItalic = pstade::integral_cast<BYTE>(dwItalic);
		lf.lfUnderline = pstade::integral_cast<BYTE>(dwUnderline);
		lf.lfStrikeOut = pstade::integral_cast<BYTE>(dwStrikeOut);
		lf.lfCharSet = pstade::integral_cast<BYTE>(dwCharSet);
		return true;
	}

	return false;
}

} } // namespace pstade::tomato
