#pragma once

#include "./union.hpp"

namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
bool is_subset_of(Flags0 fs0, Flags1 fs1)
{
	return candy::union_(fs0, fs1) == fs1;
}


} } // namespace pstade::candy
