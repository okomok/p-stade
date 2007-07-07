#ifndef PSTADE_GRAVY_ENABLE_WINDOW_HPP
#define PSTADE_GRAVY_ENABLE_WINDOW_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// 'CCmdUI::Enable' of MFC7


#include <pstade/pod_constant.hpp>
#include "./sdk/windows.hpp"
#include "./window_ptr.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_enable_window
    {
        typedef void result_type;

        void operator()(window_ref wnd, bool on) const
        {
            // if control has the focus, move the focus before disabling
            if (!on && (::GetFocus() == wnd)) {
                window_ptr parent = ::GetParent(wnd);
                if (parent)
                    ::SendMessage(*parent, WM_NEXTDLGCTL, 0, FALSE);
            }

            // never fails
            ::EnableWindow(wnd, on);
        }
    };


    PSTADE_POD_CONSTANT((op_enable_window), enable_window) = {};


} } // namespace pstade::gravy


#endif
