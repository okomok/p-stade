#pragma once

#include <pstade/unused.hpp>
#include <pstade/workaround/adl_barrier.hpp>
#include "../config/nullary_parser.hpp"
#include "../state/is_end.hpp"
#include "./not_fwd.hpp"

namespace pstade { namespace biscuit {


PSTADE_WORKAROUND_ADL_BARRIER_OPEN(end) // for boost::const_end

///////////////////////////////////////////////////////////////////////////////
// end
//
PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(end)
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		pstade::unused(us);
		return biscuit::state_is_end(s);
	}
};

PSTADE_WORKAROUND_ADL_BARRIER_CLOSE(end)


///////////////////////////////////////////////////////////////////////////////
// not end
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(end) >
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		pstade::unused(us);
		return !biscuit::state_is_end(s);
	}
};


} } // namespace pstade::biscuit
