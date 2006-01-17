#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./enum_child_windows.hpp"
#include "./is_mdi_client_and_child.hpp"

namespace pstade { namespace tomato {


namespace for_each_mdi_child_window_detail {

	template< class Functor >
	struct functor_type
	{
		Functor fun;
		functor_type(Functor f) : fun(f) { }
		bool operator()(HWND hWnd)
		{
			if (tomato::is_mdi_client_and_child(hWnd))
				fun(hWnd);

			return true; // continue
		}
	};

} // namespace for_each_mdi_child_window_detail


template< class Functor > inline
Functor for_each_mdi_child_window(HWND hWndMDIClient, Functor fun)
{
	ATLASSERT(tomato::is_valid(hWndMDIClient));

	return tomato::enum_child_windows(
		hWndMDIClient, 
		for_each_mdi_child_window_detail::functor_type<Functor>(fun)
	).fun;
}


} } // namespace pstade::tomato
