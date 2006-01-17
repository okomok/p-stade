#pragma once

#include "./detail/for_each_child_window_fun.hpp"
#include "./enum_child_windows.hpp"

namespace pstade { namespace tomato {


template< class Functor > inline
Functor for_each_toplevel_window(Functor fun)
{
	return tomato::enum_child_windows(
		NULL,
		detail::for_each_child_window_fun<Functor>(fun)
	).fun;
}


} } // namespace pstade::tomato
