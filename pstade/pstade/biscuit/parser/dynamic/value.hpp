#pragma once

#include "../../state/increment.hpp"
#include "../../state/is_end.hpp"

namespace pstade { namespace biscuit {


template< class ValueFtor >
struct value
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (biscuit::state_is_end(s))
			return false;

		if (ValueFtor()(us) != *s.get_cur())
			return false;

		biscuit::state_increment(s);
		return true;
	}
};


} } // namespace pstade::biscuit
