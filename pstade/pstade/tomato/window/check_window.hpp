#ifndef PSTADE_TOMATO_WINDOW_CHECK_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_CHECK_WINDOW_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/candy/test.hpp>
#include <pstade/check.hpp>
#include "../diet/valid.hpp"
#include "./send_message.hpp"


namespace pstade { namespace tomato {


inline
void check_window(HWND hWnd, int state)
{
    BOOST_ASSERT(diet::valid(hWnd));

    // we can only check buttons or controls acting like buttons
    LRESULT code = tomato::send_message(hWnd, WM_GETDLGCODE);
    if (candy::test(code, DLGC_BUTTON))
        PSTADE_CHECK(tomato::send_message(hWnd, BM_SETCHECK, state) == 0);
}


} } // namespace pstade::tomato


#endif
