#pragma once

#include "./count.hpp"
#include "./remove.hpp"

namespace pstade { namespace candy {


template< class Flags, class Flag > inline
Flags& reset(Flags& fs, Flag f)
{
	ATLASSERT(candy::count(f) == 1);

	return candy::remove(fs, f);
}

template< class Flags > inline
Flags& reset(Flags& flags)
{
	flags = 0;
	return flags;
}


} } // namespace pstade::candy
