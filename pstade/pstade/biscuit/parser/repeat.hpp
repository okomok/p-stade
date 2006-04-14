#ifndef PSTADE_BISCUIT_PARSER_REPEAT_HPP
#define PSTADE_BISCUIT_PARSER_REPEAT_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/static_assert.hpp>
#include "../state/cur_guard.hpp"


namespace pstade { namespace biscuit {


template< class Parser, unsigned int min, unsigned int max = min >
struct repeat // greedy
{
	BOOST_STATIC_ASSERT(min <= max);

	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_cur_guard<State> gd(s);

		for (unsigned int i = 0; i < max; ++i) {
			if (!Parser::parse(s, us)) {
				if (i < min) // not enough
					return false;
			}
		}

		gd.dismiss();
		return true;
	}
};


} } // namespace pstade::biscuit


#endif
