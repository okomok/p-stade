#pragma once

#include "../meta/uint.hpp"

namespace pstade { namespace tomato {


struct rebar_band_runtime_styles :
	uint<RBBS_BREAK | RBBS_HIDDEN | RBBS_NOGRIPPER>
{ };


} } // namespace pstade::tomato
