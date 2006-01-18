#pragma once

#include "./bchrng.hpp"

namespace pstade { namespace biscuit {


template< char min_ch, char max_ch >
struct chrng :
	bchrng< char, min_ch, max_ch >
{ };


} } // namespace pstade::biscuit
