#pragma once

#include "./complement.hpp"
#include "./mask.hpp"

namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
Flags0& remove(Flags0& fs0, Flags1 fs1)
{
	return candy::mask(fs0, candy::complement(fs1));
}


} } // namespace pstade::candy
