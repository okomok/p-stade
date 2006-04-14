#ifndef PSTADE_KETCHUP_CMD_UI_IMPL_CHILDWINDOW_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_IMPL_CHILDWINDOW_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright 2005 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/window/check_window.hpp>
#include <pstade/tomato/window/enable_window.hpp>
#include <pstade/tomato/window/set_window_text.hpp>
#include "../cmd_ui.hpp"


namespace pstade { namespace ketchup {


struct childwindow_cmd_ui : cmd_ui
{
	explicit childwindow_cmd_ui(UINT uID, HWND hWndChild) :
		cmd_ui(uID), m_hWndChild(hWndChild)
	{
		BOOST_ASSERT(diet::valid(hWndChild));
	}

protected:
	virtual void enable_impl(bool on)
	{
		tomato::enable_window(m_hWndChild, on);
	}

	virtual void set_check_impl(int state)
	{
		// we can only check buttons or controls acting like buttons
		tomato::check_window(m_hWndChild, state);
	}

	virtual void set_text_impl(const TCHAR *pszText)
	{
		BOOST_ASSERT(diet::valid(pszText));

		tomato::set_window_text(m_hWndChild, pszText);
	}

private:
	HWND m_hWndChild;
};


} } // namespace pstade::ketchup


#endif
