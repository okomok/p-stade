#ifndef PSTADE_TOMATO_WND_CLASS_HPP
#define PSTADE_TOMATO_WND_CLASS_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include "./atl/win.hpp" // CWndClassInfo


namespace pstade { namespace tomato {


    template< class Wnd > inline
    ATL::CWndClassInfo& wnd_class(TCHAR const *WndClassName)
    {
        static ATL::CWndClassInfo wc =
        {
            {
                sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, &Wnd::StartWindowProc,
                0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, WndClassName, NULL
            },
            NULL, NULL, IDC_ARROW, TRUE, 0, _T("")
        };

        return wc;
    }


    template< class Wnd > inline
    ATL::CWndClassInfo& wnd_class_ex(TCHAR const *WndClassName, UINT style, UINT bkgnd = -1)
    {
        static ATL::CWndClassInfo wc =
        {
            {
                sizeof(WNDCLASSEX), style, &Wnd::StartWindowProc,
                0, 0, NULL, NULL, NULL, (HBRUSH)(bkgnd + 1), NULL, WndClassName, NULL
            },
            NULL, NULL, IDC_ARROW, TRUE, 0, _T("")
        };

        return wc;
    }


    template< class Wnd > inline
    ATL::CWndClassInfo& wnd_superclass(TCHAR const *WndClassName, TCHAR const *OrgWndClassName)
    {
        static ATL::CWndClassInfo wc =
        {
            {
                sizeof(WNDCLASSEX), style, &Wnd::StartWindowProc,
                0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL
            },
            OrigWndClassName, NULL, NULL, TRUE, 0, _T("")
        };

        return wc;
    }


} } // namespace pstade::tomato


#endif
