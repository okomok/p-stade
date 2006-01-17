#pragma once

#include "../../state/actionable_guard.hpp"

namespace pstade { namespace biscuit {


template< class Parser >
struct no_actions
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_actionable_guard<State> sa(s, false);
		return Parser::parse(s, us);
	}
};


} } // namespace pstade::biscuit
