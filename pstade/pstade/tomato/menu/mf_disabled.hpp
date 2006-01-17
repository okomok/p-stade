#pragma once

#include "../meta/uint.hpp"

namespace pstade { namespace tomato {


struct mf_disabled :
#if !defined(_WIN32_WCE)
	uint<MF_DISABLED>
#else
	uint<0>
#endif // !defined(_WIN32_WCE)
{ };


} } // namespace pstade::tomato
