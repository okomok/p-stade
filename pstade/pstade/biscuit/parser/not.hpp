#ifndef PSTADE_BISCUIT_PARSER_NOT_HPP
#define PSTADE_BISCUIT_PARSER_NOT_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/range/result_iterator.hpp>
#include <pstade/if_debug.hpp>
#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "../state/cur_guard.hpp"
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "./identity.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct not_ // one character parser
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (biscuit::state_is_end(s))
			return false;

		state_cur_guard<State> gd(s);

		if (Parser::parse(s, us)) {
			PSTADE_IF_DEBUG (
				typedef typename boost::range_result_iterator<State>::type iter_t;
				iter_t one_step_forward; { one_step_forward = gd.marker(); ++one_step_forward; }
				BOOST_ASSERT(s.get_cur() == one_step_forward && "pstade::biscuit::not_ - not_ is defined only if one character parser.");
			)

			return false;
		}

		biscuit::state_increment(s);

		gd.dismiss();
		return true;
	}
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


template< class Parser >
struct not_< not_<Parser> > :
	identity<Parser>
{ };


#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


} } // namespace pstade::biscuit


#endif
