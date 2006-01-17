#pragma once

#include <pstade/tomato/diagnostic/is_valid.hpp>
#include "../cmd_ui.hpp"

namespace pstade { namespace ketchup {


template< class MultiPaneStatusBarCtrl >
struct multipanestatusbar_cmd_ui : cmd_ui
{
	multipanestatusbar_cmd_ui(UINT nPaneID, MultiPaneStatusBarCtrl& statusbar, int index) :
		cmd_ui(nPaneID), m_statusbar(statusbar), m_index(index)
	{
		ATLASSERT(tomato::is_valid(statusbar));
	}

protected:
	virtual void set_text_impl(LPCTSTR lpstrText)
	{
		m_statusbar.SetPaneText(get_id(), lpstrText);
	}

private:
	MultiPaneStatusBarCtrl& m_statusbar;
	int m_index;
};


} } // namespace pstade::ketchup
