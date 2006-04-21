#ifndef PSTADE_KETCHUP_CORE_COMPATIBILITY_HPP
#define PSTADE_KETCHUP_CORE_COMPATIBILITY_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
