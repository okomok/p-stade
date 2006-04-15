#ifndef PSTADE_KETCHUP_CORE_PROCESS_WINDOW_MESSAGE_HPP
#define PSTADE_KETCHUP_CORE_PROCESS_WINDOW_MESSAGE_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include "./access.hpp"
#include "./process_window_message_fwd.hpp"


namespace pstade { namespace ketchup {


template< class MessageProcessor, class Derived > inline
BOOL process_window_message(const MessageProcessor& processor, Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
{
	return access::process_window_message(processor, derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
}


template< class DerivedMessageProcessor > inline
BOOL process_window_message(DerivedMessageProcessor& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
{
	return process_window_message(derived, derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
}


} } // namespace pstade::ketchup


#endif
