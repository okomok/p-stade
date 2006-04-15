#ifndef PSTADE_BISCUIT_PARSER_BEFORE_HPP
#define PSTADE_BISCUIT_PARSER_BEFORE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include "../state/cur_guard.hpp"
#include "./not.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct before
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		state_cur_guard<State> gd(s);
		return Parser::parse(s, us);
	}
};


// for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//
template< class Parser >
struct not_before
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		return !before<Parser>::parse(s, us);
	}
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	template< class Parser >
	struct not_< before<Parser> >
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			return !before<Parser>::parse(s, us);
		}
	};

#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


} } // namespace pstade::biscuit


#endif
