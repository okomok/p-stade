#pragma once

#include "./empty.hpp"
#include "./intersection.hpp"

namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
bool test_any(Flags0 fs0, Flags1 fs1)
{
	return !candy::empty(candy::intersection(fs0, fs1));
}


} } // namespace pstade::candy
