#ifndef PSTADE_BISCUIT_PARSER_PRIMITIVE_BCHRNG_HPP
#define PSTADE_BISCUIT_PARSER_PRIMITIVE_BCHRNG_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unused.hpp>
#include "../../state/increment.hpp"
#include "../../state/is_end.hpp"


namespace pstade { namespace biscuit {


template< class T, T min_ch, T max_ch >
struct bchrng
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (biscuit::state_is_end(s))
			return false;

		if (min_ch <= *s.get_cur() && *s.get_cur() <= max_ch) {
			biscuit::state_increment(s);
			return true;
		}

		pstade::unused(us);
		return false;
	}
};


} } // namespace pstade::biscuit


#endif
