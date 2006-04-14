#ifndef PSTADE_TOMATO_WINDOW_CHILD_WINDOWS_HPP
#define PSTADE_TOMATO_WINDOW_CHILD_WINDOWS_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not Range:
//
// It is impossible without additional resources.


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/utility/addressof.hpp>
#include "../boolean_cast.hpp"
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


namespace child_windows_detail {


	template< class EnumFtor >
	BOOL CALLBACK proc(HWND hWnd, LPARAM lParam)
	{
		BOOST_ASSERT(diet::valid(hWnd));

		EnumFtor *pfun = reinterpret_cast<EnumFtor *>(lParam);
		return tomato::boolean((*pfun)(hWnd));
	}


	template< class EnumFtor >
	EnumFtor enumerate(HWND hWndParent, EnumFtor fun)
	{
		// Note:
		//   if no child, EnumChildWindows "fails"
		//   and the GetLastError value is undocumented.
		//   So there seems no way to know whether or not
		//   api failed.
		::EnumChildWindows(
			hWndParent,
			&proc<EnumFtor>,
			reinterpret_cast<LPARAM>(boost::addressof(fun))
		);

		return fun;
	}


} // namespace child_windows_detail


struct child_windows
{
	typedef child_windows pstade_sausage_enumerable;

	explicit child_windows(HWND hWndParent) :
		m_hWndParent(hWndParent)
	{
		// NULL means the root window.
		BOOST_ASSERT(hWndParent == NULL || diet::valid(hWndParent));
	}

	HWND parent() const
	{
		return m_hWndParent;
	}

private:
	HWND m_hWndParent;

public:
	typedef HWND pstade_sausage_enumerate_argument_type;

	template< class EnumFtor >
	EnumFtor pstade_sausage_enumerate(EnumFtor fun) const
	{
		return child_windows_detail::enumerate(m_hWndParent, fun);
	}
};


} } // namespace pstade::tomato


#endif
