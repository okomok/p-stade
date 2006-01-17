#pragma once

namespace pstade { namespace biscuit {


template<
	class InitFtor, class ConditionFtor,
	class StepFtor, class BodyParser
>
struct for_
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		for (InitFtor()(us); ConditionFtor()(us); StepFtor()(us)) {
			if (!BodyParser::parse(s, us))
				return false;
		}

		return true;
	}
};


} } // namespace pstade::biscuit
