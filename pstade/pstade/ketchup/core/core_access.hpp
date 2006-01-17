#pragma once

#include <boost/config.hpp> // for BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#include <boost/type.hpp>
#include <pstade/unused.hpp>
#include <pstade/tomato/cast/boolean_cast.hpp>
#include "./process_window_message_fwd.hpp"

namespace pstade { namespace ketchup {


class core_access
{

#if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
public:
#else // VC8

	template< class MessageProcessor, class Derived >
	friend BOOL process_window_message(const MessageProcessor& processor, Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID);

	template< class ChainClass, DWORD msgMapID >
	friend struct chain_msg_map_entry_set::chain_msg_map_alt;
#endif // defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

	template< class MessageProcessor, class Derived >
	static BOOL process_window_message(const MessageProcessor& processor, Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		pstade::unused(processor);

		return tomato::auto_bool(processor.end_msg_map.process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID));
	}

	// Note:
	//   As this code seems to be difficult for broken compilers,
	//   BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE cannot work around BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS.
	template< class ChainClass, class msgMapID_t, class Derived >
	static bool chain_msg_map_alt(
		Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID,
		boost::type<ChainClass>, msgMapID_t
	)
	{
		pstade::unused(dwMsgMapID);

		return tomato::auto_bool(derived.ChainClass::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, msgMapID_t::value));
	}

	// Note:
	//   CDynamicChain must be derived as public, but what if CallChain were private? So I define...
	template< class dynaChainID_t, class Derived >
	static bool chain_msg_map_dynamic(
		Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID,
		dynaChainID_t
	)
	{
		pstade::unused(dwMsgMapID);

		return tomato::auto_bool(derived.ATL::CDynamicChain::CallChain(dynaChainID_t::value, hWnd, uMsg, wParam, lParam, lResult));
	}

}; // class core_access


} } // namespace pstade::ketchup
