#pragma once

#include "./process_window_message.hpp"


#define PSTADE_KETCHUP_CHAIN_MSG(map) \
	{ \
		if (pstade::ketchup::process_window_message(map, *this, hWnd, uMsg, wParam, lParam, lResult, 0)) \
			return TRUE; \
	} \
/**/


#define PSTADE_KETCHUP_CHAIN_MSG_ALT(map, msgMapID) \
	{ \
		if (pstade::ketchup::process_window_message(map, *this, hWnd, uMsg, wParam, lParam, lResult, msgMapID)) \
			return TRUE; \
	} \
/**/
