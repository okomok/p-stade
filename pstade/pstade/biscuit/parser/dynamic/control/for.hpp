#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_CONTROL_FOR_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_CONTROL_FOR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
