#pragma once

#include "./bchar.hpp"

namespace pstade { namespace biscuit {


template< char ch >
struct char_ :
	bchar< char, ch >
{ };


} } // namespace pstade::biscuit
