#pragma once

#include <pstade/assert.hpp>

namespace pstade { namespace biscuit {


struct pigs_fly
{
	template< class ParsingSubRange, class UserState >
	void operator()(ParsingSubRange&, UserState&) const
	{
		PSTADE_ASSERT(false && "pstade::biscuit::pigs_fly - When pigs fly.");
	}
};


} } // namespace pstade::biscuit
