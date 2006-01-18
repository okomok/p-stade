#pragma once

#include <boost/config.hpp> // for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include "./star.hpp"
#include "./not.hpp"

namespace pstade { namespace biscuit {


template< class Parser >
struct plus
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (!Parser::parse(s, us))
			return false;

		return star<Parser>::parse(s, us);
	}
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	///////////////////////////////////////////////////////////////////////////////
	// not_ plus
	//
	template< class Parser >
	struct not_< plus<Parser> >
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			return !Parser::parse(s, us);
		}
	};

#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


} } // namespace pstade::biscuit
