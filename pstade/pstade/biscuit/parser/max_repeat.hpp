#pragma once

#include "./repeat.hpp"

namespace pstade { namespace biscuit {


template< class Parser, unsigned int max >
struct max_repeat :
	repeat<Parser, 0, max>
{ };


} } // namespace pstade::biscuit
