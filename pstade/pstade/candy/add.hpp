#pragma once

#include "./union.hpp"

namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
Flags0& add(Flags0& fs0, Flags1 fs1)
{
	fs0 = candy::union_(fs0, fs1);
	return fs0;
}


} } // namespace pstade::candy
