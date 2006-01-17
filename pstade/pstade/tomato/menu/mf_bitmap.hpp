#pragma once

#include "../meta/uint.hpp"

namespace pstade { namespace tomato {


struct mf_bitmap :
#if !defined(_WIN32_WCE)
	uint<MF_BITMAP>
#else
	// See: wce400/STANDARDSDK/Mfc/Src/wceimpl.h
	uint<0x00000004L>
#endif // !defined(_WIN32_WCE)
{ };


} } // namespace pstade::tomato
