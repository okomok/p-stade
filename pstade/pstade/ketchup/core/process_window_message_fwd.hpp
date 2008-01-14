#ifndef PSTADE_KETCHUP_CORE_PROCESS_WINDOW_MESSAGE_FWD_HPP
#define PSTADE_KETCHUP_CORE_PROCESS_WINDOW_MESSAGE_FWD_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/sdk/windows.hpp>


namespace pstade { namespace ketchup {


template< class MessageMap, class Derived >
BOOL process_window_message(const MessageMap& map, Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0);


} } // namespace pstade::ketchup


#endif
