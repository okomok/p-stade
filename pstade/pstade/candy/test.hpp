#pragma once

// Note. Some win32 flags can be 0; it's dangerous.

#include <pstade/assert.hpp>
#include "./count.hpp"
#include "./empty.hpp"
#include "./intersection.hpp"

namespace pstade { namespace candy {


template< class Flags, class Flag > inline
bool test(Flags fs, Flag f)
{
	PSTADE_ASSERT(candy::count(f) == 1 && "pstade::candy::test - multiple flags are not allowed.");

	return !candy::empty(candy::intersection(fs, f));
}


} } // namespace pstade::candy
