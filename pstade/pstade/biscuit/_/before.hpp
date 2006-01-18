#pragma once

#include <boost/config.hpp> // for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include "../state/cur_guard.hpp"
#include "./not.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// before
//
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


///////////////////////////////////////////////////////////////////////////////
// not_before for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
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

	//////////////////////////////////////////////////////////////////////////////
	// not_ before
	//
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
