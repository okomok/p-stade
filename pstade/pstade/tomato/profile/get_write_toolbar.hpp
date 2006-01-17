#pragma once

#include <atlctrls.h>
#include <boost/scoped_array.hpp>
#include <pstade/candy/test.hpp>
#include <pstade/integral_cast.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../meta/dword.hpp"
#include "./query_dword.hpp"
#include "./set_dword.hpp"

// Note:
//   button-count or something must be saved, because "0 button toolbar" is valid.
//   And you need not remove redundant values thanks to button-count.

namespace pstade { namespace tomato {


struct separator_iBitmap : dword<25964951>
{ };


namespace profile_toolbar_detail {

	inline void tbBtn_separator_initialize(TBBUTTON& tbBtn)
	{
		tbBtn.iBitmap = 8;
		tbBtn.idCommand = 0;
		tbBtn.fsState = 0;
		tbBtn.fsStyle = TBSTYLE_SEP;
		tbBtn.dwData = 0;
		tbBtn.iString = 0;
	}

	template< class StringT > inline
	StringT format_toolbar_button_value_name(StringT& buf, const StringT& prefix, int i)
	{
		ATLASSERT(buf.IsEmpty());

		buf = prefix + _T("toolbar.button[");
		buf.Append(i);
		buf += _T("].iBitmap");
		return buf;
	}

	inline void clean_up_toolbar_buttons(HWND hWndToolBar)
	{
		ATLASSERT(tomato::is_valid(hWndToolBar));
		
		WTL::CToolBarCtrl toolbar(hWndToolBar);
		while (toolbar.DeleteButton(0))
			;
	}

} // namespace profile_toolbar_detail


template< class StringT, class Profile >
void profile_write_toolbar(Profile& pr, HWND hWndToolBar, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWndToolBar));
	
	WTL::CToolBarCtrl toolbar(hWndToolBar);

	int count = toolbar.GetButtonCount();
	profile_set_dword(pr, prefix + _T("toolbar.buttonCount"), count);

	for (int i = 0; i < count; ++i) {
		TBBUTTON tbBtn;
		tomato::api_verify(toolbar.GetButton(i, &tbBtn));

		StringT val_name;
		profile_toolbar_detail::format_toolbar_button_value_name(val_name, prefix, i);

		DWORD nIndex = candy::test(tbBtn.fsStyle, TBSTYLE_SEP) ? separator_iBitmap::value : tbBtn.iBitmap;
		tomato::profile_set_dword(pr, val_name, nIndex);
	}
}


// hWndToolbar must have all the buttons before calling.
template< class StringT, class Profile >
bool profile_get_toolbar(Profile& pr, HWND hWndToolBar, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWndToolBar));

	WTL::CToolBarCtrl toolbar(hWndToolBar);

	DWORD dwCount;
	if (!tomato::profile_query_dword(pr, prefix + _T("toolbar.buttonCount"), dwCount))
		return false;

	int count = toolbar.GetButtonCount();
	boost::scoped_array<TBBUTTON> pTBBtn(new TBBUTTON[count]);

	// save original tbbuttons
	for (int i = 0; i < count; ++i) {
		TBBUTTON tbBtn;
		tomato::api_verify(toolbar.GetButton(i, &tbBtn));
		pTBBtn[i] = tbBtn;
	}

	profile_toolbar_detail::clean_up_toolbar_buttons(hWndToolBar);

	// insert buttons
	for (DWORD dwIndex = 0; dwIndex < dwCount; ++dwIndex) {
		StringT val_name;
		profile_toolbar_detail::format_toolbar_button_value_name(val_name, prefix, dwIndex);

		DWORD dwBitmap;
		if (!tomato::profile_query_dword(pr, val_name, dwBitmap)) // never trust dwCount
			break;

		if (dwBitmap == separator_iBitmap::value) {
			TBBUTTON tbBtn;
			profile_toolbar_detail::tbBtn_separator_initialize(tbBtn);
			tomato::api_verify(toolbar.InsertButton(toolbar.GetButtonCount(), &tbBtn));
		}
		else {
			int j = 0;
			for ( ; j < count; ++j) { // look up corresponding iBitmap
				if (!candy::test(pTBBtn[j].fsStyle, TBSTYLE_SEP) &&
					pTBBtn[j].iBitmap == pstade::integral_cast<int>(dwBitmap))
				{
					tomato::api_verify(toolbar.InsertButton(toolbar.GetButtonCount(), &pTBBtn[j]));
					break;
				}
			}

			if (j == count) { // not found
				ATLTRACE2(WTL::atlTraceUI, 0, _T("pstade::tomato::get_toolbar_profile: warning - %d iBitmap not found.\n"), dwBitmap);
				ATLASSERT(false);
			}
		}
	} // for

	return true;
}


// cannot be the same name because of CToolBarCtrl
template< class StringT, class Profile, class OutIter >
bool profile_copy_toolbar(Profile& pr, OutIter out, const StringT& prefix)
{
	DWORD dwCount;
	if (!tomato::profile_query_dword(pr, prefix + _T("toolbar.buttonCount"), dwCount))
		return false;

	// copy button index
	for (DWORD dwIndex = 0; dwIndex < dwCount; ++dwIndex) {
		StringT val_name;
		profile_toolbar_detail::format_toolbar_button_value_name(val_name, prefix, dwIndex);

		DWORD dwBitmap;
		if (!tomato::profile_query_dword(pr, val_name, dwBitmap))
			break;
    
		*out = pstade::integral_cast<int>(dwBitmap);
		++out;
	}

	return true;
}


} } // namespace pstade::tomato
