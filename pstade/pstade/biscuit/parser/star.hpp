#ifndef PSTADE_BISCUIT_PARSER_STAR_HPP
#define PSTADE_BISCUIT_PARSER_STAR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/if_debug.hpp>
#include "./begin.hpp"
#include "./end.hpp"
#include "./eps.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct star
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		// Note:
		//   YARD has state_is_end(s) check at entrance,
		//   but it seems redundant.

		for (;;) {
			PSTADE_IF_DEBUG (
				typedef typename boost::range_result_iterator<State>::type iter_t;
				iter_t const marker = s.get_cur();
			)

			if (!Parser::parse(s, us))
				break;

			PSTADE_IF_DEBUG (
				iter_t const cur = s.get_cur();
				BOOST_ASSERT(marker != cur &&
					"pstade::biscuit::star - Parser must advance on star-operation; 'end/eol' are the usual suspects,"
					"or iterator's comparison operator is broken.");
			)
		}

		return true;
	}
};


// meaningless
//
template<>
struct star< PSTADE_BISCUIT_NULLARY_PARSER(begin) >;

template<>
struct star< PSTADE_BISCUIT_NULLARY_PARSER(end) >;

template<>
struct star< PSTADE_BISCUIT_NULLARY_PARSER(eps) >;


} } // namespace pstade::biscuit


#endif
