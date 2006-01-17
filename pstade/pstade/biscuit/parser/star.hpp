#pragma once

#include <boost/range/result_iterator.hpp>
#include <pstade/assert.hpp>
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

		for (;;)
		{
		#if defined(_DEBUG)
			typename boost::range_result_iterator<State>::type const marker = s.get_cur();
		#endif

			if (!Parser::parse(s, us))
				break;

		#if defined(_DEBUG)
			PSTADE_ASSERT(marker != s.get_cur() && "pstade::biscuit::star - Parser must advance on star-operation; 'end/eol' is a usual suspect.");
		#endif
		}

		return true;
	}
};

///////////////////////////////////////////////////////////////////////////////
// meaningless
//
template<>
struct star< PSTADE_BISCUIT_NULLARY_PARSER(begin) >;

template<>
struct star< PSTADE_BISCUIT_NULLARY_PARSER(end) >;

template<>
struct star< PSTADE_BISCUIT_NULLARY_PARSER(eps) >;


} } // namespace pstade::biscuit
