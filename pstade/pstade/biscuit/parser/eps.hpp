#ifndef PSTADE_BISCUIT_PARSER_EPS_HPP
#define PSTADE_BISCUIT_PARSER_EPS_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "./not_fwd.hpp"


namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(eps)
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		pstade::unused(s, us);
		return true;
	}
};


template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(eps) >;


} } // namespace pstade::biscuit


#endif
