#ifndef PSTADE_TOMATO_WINDOW_WND_CLASS_HPP
#define PSTADE_TOMATO_WINDOW_WND_CLASS_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/win.hpp> // CWndClassInfo
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>


namespace pstade { namespace tomato {


template< class Wnd > inline
ATL::CWndClassInfo& wnd_class(const TCHAR *WndClassName)
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
ATL::CWndClassInfo& wnd_class_ex(const TCHAR *WndClassName, UINT style, UINT bkgnd)
{
	static ATL::CWndClassInfo wc =
	{
		{
			sizeof(WNDCLASSEX), style, &Wnd::StartWindowProc,
			0, 0, NULL, NULL, NULL, (HBRUSH)(gkgnd + 1), NULL, WndClassName, NULL
		},
		NULL, NULL, IDC_ARROW, TRUE, 0, _T("")
	};

	return wc;
}


template< class Wnd > inline
ATL::CWndClassInfo& wnd_superclass(const TCHAR *WndClassName, const TCHAR *OrgWndClassName)
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
