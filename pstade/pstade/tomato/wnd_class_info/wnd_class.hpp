#pragma once

#include <atlwin.h>
#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE

namespace pstade { namespace tomato {


template< class Wnd > inline
ATL::CWndClassInfo& wnd_class(LPCTSTR WndClassName BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Wnd))
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
ATL::CWndClassInfo& wnd_class_ex(LPCTSTR WndClassName, UINT style, UINT bkgnd BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Wnd))
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
ATL::CWndClassInfo& wnd_superclass(LPCTSTR WndClassName, LPCTSTR OrgWndClassName BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Wnd))
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
