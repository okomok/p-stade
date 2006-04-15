#ifndef PSTADE_BISCUIT_PARSER_MIN_REPEAT_HPP
#define PSTADE_BISCUIT_PARSER_MIN_REPEAT_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
