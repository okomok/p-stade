#ifndef PSTADE_TOMATO_REBAR_REBAR_BAND_RUNTIME_STYLES_HPP
#define PSTADE_TOMATO_REBAR_REBAR_BAND_RUNTIME_STYLES_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include "../meta/uint.hpp"


namespace pstade { namespace tomato {


struct rebar_band_runtime_styles :
	uint<RBBS_BREAK | RBBS_HIDDEN | RBBS_NOGRIPPER>
{ };


} } // namespace pstade::tomato


#endif
