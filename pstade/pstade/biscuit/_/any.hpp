#pragma once

#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "./not_fwd.hpp"
#include "./nothing.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// any
//
PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(any)
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (biscuit::state_is_end(s))
			return false;

		biscuit::state_increment(s);

		pstade::unused(us);
		return true;
	}
};


///////////////////////////////////////////////////////////////////////////////
// not any
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(any) > :
	PSTADE_BISCUIT_NULLARY_PARSER(nothing)
{ };


} } // namespace pstade::biscuit
