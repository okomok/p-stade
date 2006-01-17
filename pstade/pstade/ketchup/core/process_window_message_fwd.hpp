#pragma once

namespace pstade { namespace ketchup {


template< class MessageMap, class Derived >
BOOL process_window_message(const MessageMap& map, Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0);


} } // namespace pstade::ketchup
