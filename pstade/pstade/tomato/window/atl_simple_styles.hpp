#pragma once

#include <atlframe.h>
#include "../meta/dword.hpp"

namespace pstade { namespace tomato {


struct atl_simple_toolbar_style :
	dword<ATL_SIMPLE_TOOLBAR_STYLE>
{ };

struct atl_simple_toolbar_pane_style :
	dword<ATL_SIMPLE_TOOLBAR_PANE_STYLE>
{ };

struct atl_simple_rebar_style :
	dword<ATL_SIMPLE_REBAR_STYLE>
{ };

struct atl_simple_rebar_noborder_style :
	dword<ATL_SIMPLE_REBAR_NOBORDER_STYLE>
{ };


} } // namespace pstade::tomato

#if !defined(_WIN32_WCE)

	#include <atlctrlw.h>

	namespace pstade { namespace tomato {

	struct atl_simple_cmdbar_pane_style :
		dword<ATL_SIMPLE_CMDBAR_PANE_STYLE>
	{ };


	} } // namespace pstade::tomato

#endif // !defined(_WIN32_WCE)
