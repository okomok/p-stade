#pragma once

#include "./core_access.hpp"
#include "./process_window_message_fwd.hpp"

namespace pstade { namespace ketchup {


template< class MessageProcessor, class Derived > inline
BOOL process_window_message(const MessageProcessor& processor, Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
{
	return core_access::process_window_message(processor, derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
}


template< class DerivedMessageProcessor > inline
BOOL process_window_message(DerivedMessageProcessor& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
{
	return process_window_message(derived, derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
}


} } // namespace pstade::ketchup
