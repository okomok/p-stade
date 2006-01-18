#pragma once

#include "../state/cur_guard.hpp"

namespace pstade { namespace biscuit {


template< class Parser, unsigned int min >
struct min_repeat
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_cur_guard<State> gd(s);

		for (unsigned int i = 0; i < min; ++i) {
			if (!Parser::parse(s, us))
				return false;
		}

		gd.dismiss();
		return true;
	}
};


} } // namespace pstade::biscuit
