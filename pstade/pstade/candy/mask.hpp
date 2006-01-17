#pragma once

#include "./intersection.hpp"

namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
Flags0& mask(Flags0& fs0, Flags1 fs1)
{
	fs0 = candy::intersection(fs0, fs1);
	return fs0;
}


} } // namespace pstade::candy
