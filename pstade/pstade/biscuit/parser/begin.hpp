#pragma once

#include <pstade/unused.hpp>
#include <pstade/workaround/adl_barrier.hpp>
#include "../config/nullary_parser.hpp"
#include "../state/is_begin.hpp"
#include "./not_fwd.hpp"

namespace pstade { namespace biscuit {


PSTADE_WORKAROUND_ADL_BARRIER_OPEN(begin) // for boost::const_begin

///////////////////////////////////////////////////////////////////////////////
// begin
//
PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(begin)
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		pstade::unused(us);
		return biscuit::state_is_begin(s);
	}
};

PSTADE_WORKAROUND_ADL_BARRIER_CLOSE(begin)


///////////////////////////////////////////////////////////////////////////////
// not begin
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(begin) >
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		pstade::unused(us);
		return !biscuit::state_is_begin(s);
	}
};


} } // namespace pstade::biscuit
