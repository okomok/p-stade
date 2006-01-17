#pragma once

namespace pstade { namespace biscuit {


template< class ConditionFtor, class BodyParser >
struct while_
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		while (ConditionFtor()(us)) {
			if (!BodyParser::parse(s, us))
				return false;
		}

		return true;
	}
};


} } // namespace pstade::biscuit
