#ifndef PSTADE_GRAVY_CHECK_WINDOW_HPP
#define PSTADE_GRAVY_CHECK_WINDOW_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/candy/test.hpp>
#include <pstade/check.hpp>
#include <pstade/instance.hpp>
#include "./include/windows.hpp"
#include "./send_message.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_check_window
    {
        typedef void result_type;

        void operator()(window_ref wnd, int state) const
        {
            // we can only check buttons or controls acting like buttons
            LRESULT code = send_message(wnd, WM_GETDLGCODE);
            if (candy::test(code, DLGC_BUTTON))
                PSTADE_CHECK(send_message(wnd, BM_SETCHECK, state) == 0);
        }
    };


    PSTADE_CONSTANT(check_window, (op_check_window))


} } // namespace pstade::gravy


#endif
