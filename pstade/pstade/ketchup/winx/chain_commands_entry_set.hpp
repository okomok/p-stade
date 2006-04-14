#ifndef PSTADE_KETCHUP_WINX_CHAIN_COMMANDS_ENTRY_SET_HPP
#define PSTADE_KETCHUP_WINX_CHAIN_COMMANDS_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright 2005 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include "../win/chain_msg_map_entry_set.hpp"


namespace pstade { namespace ketchup {


struct chain_commands_entry_set
{

	template< class ChainClass, DWORD msgMapID >
	struct chain_commands_alt
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			if (uMsg == WM_COMMAND)
			{
				return chain_msg_map_entry_set::chain_msg_map_alt<ChainClass, msgMapID>::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
			}
			return false;
		}
	};

	template< class ChainClass >
	struct chain_commands : chain_commands_alt<ChainClass, 0>
	{
	};


	template< class ChainFtorClass, DWORD msgMapID >
	struct chain_commands_alt_member
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			if (uMsg == WM_COMMAND)
			{
				return chain_msg_map_entry_set::chain_msg_map_alt_member<ChainFtorClass, msgMapID>::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
			}
			return false;
		}
	};

	template< class ChainFtorClass >
	struct chain_commands_member : chain_commands_alt_member<ChainFtorClass, 0>
	{
	};

};


} } // namespace pstade::ketchup


#endif
