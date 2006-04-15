#ifndef PSTADE_BISCUIT_PARSER_DIRECTIVE_LAZY_ACTIONS_HPP
#define PSTADE_BISCUIT_PARSER_DIRECTIVE_LAZY_ACTIONS_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/result_iterator.hpp>
#include "./no_actions.hpp"
#include "./no_captures.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct lazy_actions
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (!s.is_actionable())
			return Parser::parse(s, us);

		typename boost::range_result_iterator<State>::type const marker = s.get_cur();

		if (!no_captures< no_actions<Parser> >::parse(s, us))
			return false;

		// parse twice.
		s.set_cur(marker);
		return Parser::parse(s, us);
	}
};


} } // namespace pstade::biscuit


#endif
