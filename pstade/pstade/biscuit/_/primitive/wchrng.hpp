#pragma once

#include "./bchrng.hpp"

namespace pstade { namespace biscuit {


template< wchar_t min_ch, wchar_t max_ch >
struct wchrng :
	bchrng< wchar_t, min_ch, max_ch >
{ };


} } // namespace pstade::biscuit
