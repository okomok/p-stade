#pragma once

namespace pstade { namespace tomato {


inline bool is_atl_idw_band(UINT uID)
{
	return ATL_IDW_BAND_FIRST <= uID && uID <= ATL_IDW_BAND_LAST;
}


} } // namespace pstade::tomato
