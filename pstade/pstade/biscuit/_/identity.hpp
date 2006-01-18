#pragma once

namespace pstade { namespace biscuit {


template< class Parser >
struct identity
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		return Parser::parse(s, us);
	}
};


} } // namespace pstade::biscuit
