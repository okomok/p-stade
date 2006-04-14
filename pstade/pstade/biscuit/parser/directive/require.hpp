#ifndef PSTADE_BISCUIT_PARSER_DIRECTIVE_REQUIRE_HPP
#define PSTADE_BISCUIT_PARSER_DIRECTIVE_REQUIRE_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include "../../algorithm/match.hpp"
#include "../../state/cur_guard.hpp"
#include "../not.hpp"


namespace pstade { namespace biscuit {


template< class Parser, class Predicate >
struct require
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_cur_guard<State> gd(s);

		if (!Parser::parse(s, us))
			return false;

		typedef typename boost::range_result_iterator<State>::type iter_t;
		boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());

		if (!(Predicate()(rng, us)))
			return false;

		gd.dismiss();
		return true;
	}
};


template< class Parser, class Predicate >
struct state_require
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_cur_guard<State> gd(s);

		if (!Parser::parse(s, us))
			return false;

		typedef typename boost::range_result_iterator<State>::type iter_t;
		boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());

		if (!(Predicate()(s, rng, us)))
			return false;

		gd.dismiss();
		return true;
	}
};


/* That's 'and' parser's job.
// predicate
//
template< class Parser >
struct predicate
{
	template< class Range, class UserState >
	bool operator()(Range& rng, UserState& us) const
	{
		return biscuit::match<Parser>(rng, us);
	}
};


// not_predicate
//
template< class Parser >
struct not_predicate
{
	template< class Range, class UserState >
	bool operator()(Range& rng, UserState& us) const
	{
		return !biscuit::match<Parser>(rng, us);
	}
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	// not predicate
	//
	template< class Parser >
	struct not_< predicate<Parser> >
	{
		template< class Range, class UserState >
		bool operator()(Range& rng, UserState& us) const
		{
			return !biscuit::match<Parser>(rng, us);
		}
	};

#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
*/


} } // namespace pstade::biscuit


#endif
