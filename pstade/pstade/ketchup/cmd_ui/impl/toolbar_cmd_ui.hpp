#ifndef PSTADE_KETCHUP_CMD_UI_IMPL_TOOLBAR_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_IMPL_TOOLBAR_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright 2005 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/tomato/toolbar/enable_toolbar_button.hpp>
#include <pstade/tomato/toolbar/check_toolbar_button.hpp>
#include "../cmd_ui.hpp"


namespace pstade { namespace ketchup {


struct toolbar_cmd_ui : cmd_ui
{
	explicit toolbar_cmd_ui(UINT uID, HWND hWnd) :
		cmd_ui(uID), m_hWndToolBar(hWnd)
	{
		BOOST_ASSERT(diet::valid(m_hWndToolBar));
	}

protected:
	virtual void enable_impl(bool on)
	{
		tomato::enable_toolbar_button(m_hWndToolBar, get_id(), on);
	}

	virtual void set_check_impl(int state)
	{
		BOOST_ASSERT(0 <= state && state <= 2); // 0=>off, 1=>on, 2=>indeterminate

		tomato::check_toolbar_button(m_hWndToolBar, get_id(), state);
	}

private:
	HWND m_hWndToolBar;
};


} } // namespace pstade::ketchup


#endif
