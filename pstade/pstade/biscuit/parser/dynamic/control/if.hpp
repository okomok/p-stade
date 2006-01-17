#pragma once

#include "../../../config/nullary_parser.hpp"
#include "../../eps.hpp"

namespace pstade { namespace biscuit {


template<
	class ConditionFtor,
	class ThenParser,
	class ElseParser = PSTADE_BISCUIT_NULLARY_PARSER(eps)
>
struct if_
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (ConditionFtor()(us))
			return ThenParser::parse(s, us);
		else
			return ElseParser::parse(s, us);
	}
};


} } // namespace pstade::biscuit
