#pragma once

#include <pstade/unused.hpp>
#include "../../state/increment.hpp"
#include "../../state/is_end.hpp"

namespace pstade { namespace biscuit {


template< class T, T ch >
struct bchar
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (biscuit::state_is_end(s))
			return false;

		if (ch != *s.get_cur())
			return false;

		biscuit::state_increment(s);

		pstade::unused(us);
		return true;
	}
};


} } // namespace pstade::biscuit
