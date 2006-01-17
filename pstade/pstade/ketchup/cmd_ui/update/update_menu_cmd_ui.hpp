#pragma once

#include <atluser.h>
#include <pstade/tomato/diagnostic/is_valid.hpp>
#include <pstade/tomato/menu/get_menu_item_count.hpp>
#include <pstade/tomato/menu/get_menu_item_id.hpp>
#include "../impl/menu_cmd_ui.hpp"
#include "./update_cmd_ui.hpp"

namespace pstade { namespace ketchup {


namespace cmd_ui_detail {

	inline bool is_possibly_popup_menu_id(UINT uID)
	{
		return uID == static_cast<UINT>(-1);
	}

	inline bool is_separator_or_invalid_id(UINT uID)
	{
		return uID == 0;
	}

} // namespace cmd_ui_detail


inline void update_menu_cmd_ui(HWND hWndUpdater, HMENU hMenu)
{
	// See: MFC7::CFrameWnd::OnInitMenuPopup

	ATLASSERT(tomato::is_valid(hWndUpdater));
	ATLASSERT(tomato::is_valid(hMenu));

	for (int i = 0, count = tomato::get_menu_item_count(hMenu); i < count; ++i)
	{
		UINT uID = tomato::get_menu_item_id(hMenu, i);
		if (cmd_ui_detail::is_separator_or_invalid_id(uID))
			continue;

		if (cmd_ui_detail::is_possibly_popup_menu_id(uID))
		{
			// route to first item of that popup
			HMENU hSubMenu = ::GetSubMenu(hMenu, i);
			if (
				hSubMenu == NULL ||
				cmd_ui_detail::is_separator_or_invalid_id(uID = tomato::get_menu_item_id(hSubMenu, 0)) ||
				cmd_ui_detail::is_possibly_popup_menu_id(uID)
			)
			{
				continue; // first item of popup can't be routed to
			}

			// popup menu item
			menu_cmd_ui ui(uID, hMenu, i, true);
			ketchup::update_cmd_ui(hWndUpdater, ui);
		}
		else
		{
			// normal menu item
			menu_cmd_ui ui(uID, hMenu, i, false);
			ketchup::update_cmd_ui(hWndUpdater, ui);
		}

		// adjust for menu deletions and additions
		int new_count = tomato::get_menu_item_count(hMenu);
		if (new_count < count)
		{
			i -= (count - new_count);
			while (i < new_count && tomato::get_menu_item_id(hMenu, i) == uID)
				++i;
		}
		count = new_count;
	} // for
}


} } // namespace pstade::ketchup
