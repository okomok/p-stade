#pragma once

#include <boost/type.hpp>
#include <pstade/unused.hpp>
#include <pstade/tomato/cast/boolean_cast.hpp>
#include <pstade/tomato/meta/dword.hpp>
#include "../core/core_access.hpp"

namespace pstade { namespace ketchup {


struct chain_msg_map_entry_set
{

	template< class ChainClass, DWORD msgMapID >
	struct chain_msg_map_alt
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			return core_access::chain_msg_map_alt(
				derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID,
				boost::type<ChainClass>(), tomato::dword<msgMapID>()
			);
		}
	};

	template< class ChainClass >
	struct chain_msg_map : chain_msg_map_alt<ChainClass, 0>
	{
	};

	template< DWORD dynaChainID >
	struct chain_msg_map_dynamic
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			return core_access::chain_msg_map_dynamic(
				derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID,
				tomato::dword<dynaChainID>()
			);
		}
	};

	template< class F_ChainClass, DWORD msgMapID >
	struct chain_msg_map_alt_member
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			return tomato::auto_bool(F_ChainClass()(derived).ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, msgMapID));
		}
	};

	template< class ChainFtorClass >
	struct chain_msg_map_member : chain_msg_map_alt_member<ChainFtorClass, 0>
	{
	};

}; // struct chain_msg_map_entry_set


} } // namespace pstade::ketchup
