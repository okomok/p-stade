#pragma once

#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include "../state/cur_guard.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// actor
//
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


///////////////////////////////////////////////////////////////////////////////
// state_actor
//
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
