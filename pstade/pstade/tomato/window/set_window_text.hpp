#pragma once

// Port of: MFC7::AfxSetWindowText

#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <boost/type.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "./fill_window_text.hpp"

namespace pstade { namespace tomato {


inline void set_window_text(HWND hWndCtrl, LPCTSTR pszNew)
{
	ATLASSERT(tomato::is_valid(hWndCtrl));

	int newLen = lstrlen(pszNew);
	boost::array<TCHAR, 256> szOld;

	// fast check to see if text really changes (reduces flash in controls)
	if (
		newLen > szOld.static_size || // boost::size makes waring C4018
		tomato::fill_window_text(hWndCtrl, szOld) != newLen ||
		lstrcmp(boost::const_begin(szOld), pszNew) != 0
	)
	{
		tomato::api_verify(::SetWindowText(hWndCtrl, pszNew));
	}
}


} } // namespace pstade::tomato
