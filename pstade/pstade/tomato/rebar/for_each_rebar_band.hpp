#pragma once

#include <atlctrls.h>
#include "../diagnostic/is_valid.hpp"
#include "./get_rebar_band_id.hpp"

namespace pstade { namespace tomato {


template< class Functor > inline
Functor for_each_rebar_band(HWND hWndReBar, Functor fun)
{
	ATLASSERT(tomato::is_valid(hWndReBar));

	WTL::CReBarCtrl rebar(hWndReBar);
	for (int i = 0, count = rebar.GetBandCount(); i < count; ++i)
		fun(hWndReBar, tomato::get_rebar_band_id(hWndReBar, i));

	return fun;
}


} } // namespace pstade::tomato
