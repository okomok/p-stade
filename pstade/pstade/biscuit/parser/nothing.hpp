#pragma once

#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "./not_fwd.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// nothing
//
PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(nothing)
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		pstade::unused(s, us);
		return false;
	}
};


///////////////////////////////////////////////////////////////////////////////
// not nothing
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(nothing) >;


} } // namespace pstade::biscuit
