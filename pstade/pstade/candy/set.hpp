#pragma once

#include "./add.hpp"
#include "./count.hpp"

namespace pstade { namespace candy {


template< class Flags, class Flag > inline
Flags& set(Flags& fs, Flag f)
{
	ATLASSERT(candy::count(f) == 1);

	return candy::add(fs, f);
}


} } // namespace pstade::candy
