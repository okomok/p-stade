#ifndef PSTADE_BISCUIT_PARSER_ACTOR_HPP
#define PSTADE_BISCUIT_PARSER_ACTOR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include "../state/cur_guard.hpp"


namespace pstade { namespace biscuit {


template< class Parser, class Action >
struct actor
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_cur_guard<State> gd(s);

		if (!Parser::parse(s, us))
			return false;

		if (s.is_actionable()) {
			typedef typename boost::range_result_iterator<State>::type iter_t;
			boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());

			Action()(rng, us);
		}

		gd.dismiss();
		return true;
	}
};


template< class Parser, class Action >
struct state_actor
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_cur_guard<State> gd(s);

		if (!Parser::parse(s, us))
			return false;

		if (s.is_actionable()) {
			typedef typename boost::range_result_iterator<State>::type iter_t;
			boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());

			Action()(s, rng, us);
		}

		gd.dismiss();
		return true;
	}
};


} } // namespace pstade::biscuit


#endif
