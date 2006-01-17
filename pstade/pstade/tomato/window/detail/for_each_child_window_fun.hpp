#pragma once

namespace pstade { namespace tomato { namespace detail {


template< class Functor >
struct for_each_child_window_fun
{
	Functor fun;
	for_each_child_window_fun(Functor f) : fun(f) { }
	bool operator()(HWND hWnd)
	{
		fun(hWnd);
		return true; // continue
	}
};


} } } // namespace pstade::tomato::detail
