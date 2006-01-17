#pragma once

#include <atlwin.h>
#include <pstade/tomato/diagnostic/is_valid.hpp>
#include <pstade/tomato/window/send_message.hpp>
#include <pstade/tomato/window/set_window_text.hpp>
#include "../cmd_ui.hpp"

namespace pstade { namespace ketchup {


struct childwindow_cmd_ui : cmd_ui
{
	childwindow_cmd_ui(UINT uID, HWND hWndChild) :
		cmd_ui(uID), m_hWndChild(hWndChild)
	{
		ATLASSERT(tomato::is_valid(hWndChild));
	}

protected:
	virtual void enable_impl(bool on)
	{
		// See: MFC7::CCmdUI::Enable

		// if control has the focus, move the focus before disabling
		if (!on && (::GetFocus() == m_hWndChild))
		{
			HWND parent = ::GetParent(m_hWndChild);
			tomato::send_message(parent, WM_NEXTDLGCTL, 0, FALSE);
		}
		::EnableWindow(m_hWndChild, on);
	}

	virtual void set_check_impl(int state)
	{
		// we can only check buttons or controls acting like buttons
		if (tomato::send_message(m_hWndChild, WM_GETDLGCODE) & DLGC_BUTTON)
			tomato::send_message(m_hWndChild, BM_SETCHECK, state);
	}

	virtual void set_text_impl(LPCTSTR pszText)
	{
		ATLASSERT(tomato::is_valid(pszText));

		tomato::set_window_text(m_hWndChild, pszText);
	}

private:
	HWND m_hWndChild;
};


} } // namespace pstade::ketchup
