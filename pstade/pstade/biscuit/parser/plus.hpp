#ifndef PSTADE_BISCUIT_PARSER_PLUS_HPP
#define PSTADE_BISCUIT_PARSER_PLUS_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
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


#endif
