#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./detail/for_each_child_window_fun.hpp"
#include "./enum_child_windows.hpp"

namespace pstade { namespace tomato {


template< class Functor > inline
Functor for_each_child_window(HWND hWndParent, Functor fun)
{
	ATLASSERT(tomato::is_valid(hWndParent));

	return enum_child_windows(
		hWndParent,
		detail::for_each_child_window_fun<Functor>(fun)
	).fun;
}


} } // namespace pstade::tomato
