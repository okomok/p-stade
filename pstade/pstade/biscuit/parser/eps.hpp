#pragma once

#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "./not_fwd.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// eps
//
PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(eps)
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		pstade::unused(s, us);
		return true;
	}
};


///////////////////////////////////////////////////////////////////////////////
// not eps
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(eps) >;


} } // namespace pstade::biscuit
