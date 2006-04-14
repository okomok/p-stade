#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_CONTROL_IF_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_CONTROL_IF_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
