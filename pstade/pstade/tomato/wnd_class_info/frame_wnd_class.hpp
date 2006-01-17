#pragma once

#include <atlframe.h>
#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE

namespace pstade { namespace tomato {


#if !defined(_WIN32_WCE)

	template< class FrameWnd > inline
	WTL::CFrameWndClassInfo& frame_wnd_class(LPCTSTR WndClassName, UINT uCommonResourceID BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(FrameWnd))
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
	WTL::CFrameWndClassInfo& frame_wnd_class_ex(LPCTSTR WndClassName, UINT uCommonResourceID, UINT style, UINT bkgnd BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(FrameWnd))
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
	WTL::CFrameWndClassInfo& frame_wnd_superclass(LPCTSTR WndClassName, LPCTSTR OrigWndClassName, UINT uCommonResourceID BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(FrameWnd))
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
	WTL::CFrameWndClassInfo& frame_wnd_class(LPCTSTR WndClassName, UINT uCommonResourceID BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(FrameWnd))
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
	WTL::CFrameWndClassInfo& frame_wnd_class_ex(LPCTSTR WndClassName, UINT uCommonResourceID, UINT style, UINT bkgnd BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(FrameWnd))
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
	WTL::CFrameWndClassInfo& frame_wnd_superclass(LPCTSTR WndClassName, LPCTSTR OrigWndClassName, UINT uCommonResourceID BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(FrameWnd))
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
