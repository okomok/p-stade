#pragma once

namespace pstade { namespace biscuit {


template< class BodyParser, class ConditionFtor >
struct do_
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		do {
			if (!BodyParser::parse(s, us))
				return false;
		} while (ConditionFtor()(us));

		return true;
	}
};


} } // namespace pstade::biscuit
