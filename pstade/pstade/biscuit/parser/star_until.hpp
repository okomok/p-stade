#ifndef PSTADE_BISCUIT_PARSER_STAR_UNTIL_HPP
#define PSTADE_BISCUIT_PARSER_STAR_UNTIL_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include "../state/cur_guard.hpp"
#include "./begin.hpp"
#include "./end.hpp"
#include "./eps.hpp"


namespace pstade { namespace biscuit {


template< class ParserA, class ParserB >
struct star_until // -*A >> B
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_cur_guard<State> gd(s);

		while (!ParserB::parse(s, us)) {
			if (!ParserA::parse(s, us))
				return false;
		}

		gd.dismiss();
		return true;
	}
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	// meaningless
	//
	template< class ParserB >
	struct star_until< PSTADE_BISCUIT_NULLARY_PARSER(begin), ParserB >;

	template< class ParserB >
	struct star_until< PSTADE_BISCUIT_NULLARY_PARSER(end), ParserB >;

	template< class ParserB >
	struct star_until< PSTADE_BISCUIT_NULLARY_PARSER(eps), ParserB >;

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION


} } // namespace pstade::biscuit


#endif
