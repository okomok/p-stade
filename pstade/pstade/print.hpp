#pragma once

#include <algorithm> // for copy
#include <string>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/assert.hpp>


#if !defined(_WIN32_WCE)
	#include <iostream>
#else
	#include <windows.h>
	extern HWND g_pstade_print_listbox_handle;
#endif


namespace pstade {


inline void print(const std::string& msg)
{
#if !defined(_WIN32_WCE)

	std::cout << msg << std::endl;

#else

	PSTADE_ASSERT(::IsWindow(g_pstade_print_listbox_handle));

	// Workaround: broken std::string constructors
	//   This could have been pstade::oven::construct<std::wstring>(msg).
	std::wstring tmp(msg.length(), 0);
	std::copy(boost::begin(msg), boost::end(msg), boost::begin(tmp));

	::SendMessage(
		g_pstade_print_listbox_handle,
		LB_ADDSTRING, 0,
		reinterpret_cast<LPARAM>(tmp.c_str())
	);

#endif
}


} // namespace pstade
