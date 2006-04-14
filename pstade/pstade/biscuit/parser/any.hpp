#ifndef PSTADE_BISCUIT_PARSER_ANY_HPP
#define PSTADE_BISCUIT_PARSER_ANY_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "./not_fwd.hpp"
#include "./nothing.hpp"


namespace pstade { namespace biscuit {


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


template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(any) > :
	PSTADE_BISCUIT_NULLARY_PARSER(nothing)
{ };


} } // namespace pstade::biscuit


#endif
