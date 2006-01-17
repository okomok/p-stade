#pragma once

#include <pstade/unused.hpp>
#include "./update_cmd_ui_message.hpp"
#include "./update/update_menu_cmd_ui.hpp"

namespace pstade { namespace ketchup {


struct cmd_ui_entry_subset
{

	template< class Dummy = boost::mpl::void_ >
	struct chain_client_cmd_ui
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			if (uMsg == ketchup::id_update_cmd_ui_message())
			{
				HWND hWndClient = derived.m_hWndClient;
				if (hWndClient != NULL)
				{
					lResult = ::SendMessage(hWndClient, uMsg, wParam, lParam);
					return ketchup::is_cmd_ui_handled(lResult);
				}
			}
			return false;
		}
	};

	template< class Dummy = boost::mpl::void_ >
	struct chain_mdi_child_cmd_ui
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			if (uMsg == ketchup::id_update_cmd_ui_message())
			{
				HWND hWndActive = derived.MDIGetActive();
				if (hWndActive != NULL)
				{
					lResult = ::SendMessage(hWndActive, uMsg, wParam, lParam);
					return ketchup::is_cmd_ui_handled(lResult);
				} 
			}
			return false;
		}
	};

	template< class Entry, class EnableIDs >
	struct enable_cmd_ui_if_handled
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			if (uMsg == ketchup::id_update_cmd_ui_message())
			{
				bool cmd_ui_handled = Entry::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
				cmd_ui& ui = ketchup::wParam_to_cmd_ui(wParam);
				if (EnableIDs::contains(ui.get_id()))
				{
					ui.enable(cmd_ui_handled);
				}
				return cmd_ui_handled;
			}

			return false;
		}
	};

	template< class Dummy = boost::mpl::void_ >
	struct update_menu_cmd_ui
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			if (uMsg == WM_INITMENUPOPUP)
			{
				ketchup::update_menu_cmd_ui(hWnd, reinterpret_cast<HMENU>(wParam));
			}

			return false;
		}
	};

}; // struct cmd_ui_entry_subset


} } // namespace pstade::ketchup
