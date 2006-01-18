#pragma once

#include <pstade/unused.hpp>
#include "../../state/increment.hpp"
#include "../../state/is_end.hpp"

namespace pstade { namespace biscuit {


template< class T, T min_ch, T max_ch >
struct bchrng
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (biscuit::state_is_end(s))
			return false;

		if (min_ch <= *s.get_cur() && *s.get_cur() <= max_ch) {
			biscuit::state_increment(s);
			return true;
		}

		pstade::unused(us);
		return false;
	}
};


} } // namespace pstade::biscuit
