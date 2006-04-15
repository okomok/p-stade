#ifndef PSTADE_TOMATO_WINDOW_FRAME_WND_CLASS_HPP
#define PSTADE_TOMATO_WINDOW_FRAME_WND_CLASS_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/frame.hpp> // CFrameWndClassInfo


namespace pstade { namespace tomato {


#if !defined(_WIN32_WCE)


template< class FrameWnd > inline
WTL::CFrameWndClassInfo& frame_wnd_class(const TCHAR *WndClassName, UINT uCommonResourceID)
{
	static WTL::CFrameWndClassInfo wc =
	{
		{
			sizeof(WNDCLASSEX), 0, &FrameWnd::StartWindowProc,
			0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, WndClassName, NULL
		},
		NULL, NULL, IDC_ARROW, TRUE, 0, _T(""), uCommonResourceID
	};
	return wc;
}


template< class FrameWnd > inline
WTL::CFrameWndClassInfo& frame_wnd_class_ex(const TCHAR *WndClassName, UINT uCommonResourceID, UINT style, UINT bkgnd)
{
	static WTL::CFrameWndClassInfo wc =
	{
		{
			sizeof(WNDCLASSEX), style, &FrameWnd::StartWindowProc,
			0, 0, NULL, NULL, NULL, (HBRUSH)(bkgnd + 1), NULL, WndClassName, NULL
		},
		NULL, NULL, IDC_ARROW, TRUE, 0, _T(""), uCommonResourceID
	};
	return wc;
}


template< class FrameWnd > inline
WTL::CFrameWndClassInfo& frame_wnd_superclass(const TCHAR *WndClassName, const TCHAR *OrigWndClassName, UINT uCommonResourceID)
{
	static WTL::CFrameWndClassInfo wc =
	{
		{
			sizeof(WNDCLASSEX), style, &FrameWnd::StartWindowProc,
			0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL
		},
		OrigWndClassName, NULL, NULL, TRUE, 0, _T(""), uCommonResourceID
	};
	return wc;
}


#else // CE specific


template< class FrameWnd > inline
WTL::CFrameWndClassInfo& frame_wnd_class(const TCHAR *WndClassName, UINT uCommonResourceID)
{
	static CFrameWndClassInfo wc =
	{
		{
			0, &FrameWnd::StartWindowProc,
			0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, WndClassName
		},
		NULL, NULL, IDC_ARROW, TRUE, 0, _T(""), uCommonResourceID
	};
	return wc;
}


template< class FrameWnd > inline
WTL::CFrameWndClassInfo& frame_wnd_class_ex(const TCHAR *WndClassName, UINT uCommonResourceID, UINT style, UINT bkgnd)
{
	static CFrameWndClassInfo wc =
	{
		{
			style, &FrameWnd::StartWindowProc,
			0, 0, NULL, NULL, NULL, (HBRUSH)(bkgnd + 1), NULL, WndClassName
		},
		NULL, NULL, IDC_ARROW, TRUE, 0, _T(""), uCommonResourceID
	};
	return wc;
}


template< class FrameWnd > inline
WTL::CFrameWndClassInfo& frame_wnd_superclass(const TCHAR *WndClassName, const TCHAR *OrigWndClassName, UINT uCommonResourceID)
{
	static CFrameWndClassInfo wc =
	{
		{
			style, &FrameWnd::StartWindowProc,
			0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName
		},
		OrigWndClassName, NULL, IDC_ARROW, TRUE, 0, _T(""), uCommonResourceID
	};
	return wc;
}


#endif // !defined(_WIN32_WCE)


} } // namespace pstade::tomato


#endif
