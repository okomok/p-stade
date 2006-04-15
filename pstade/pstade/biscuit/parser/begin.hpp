#ifndef PSTADE_BISCUIT_PARSER_BEGIN_HPP
#define PSTADE_BISCUIT_PARSER_BEGIN_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "../state/is_begin.hpp"
#include "./not_fwd.hpp"


namespace pstade { namespace biscuit {


PSTADE_ADL_BARRIER_OPEN(begin) // for boost::const_begin


	PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(begin)
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			pstade::unused(us);
			return biscuit::state_is_begin(s);
		}
	};


PSTADE_ADL_BARRIER_CLOSE(begin)


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


#endif
