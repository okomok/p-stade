#pragma once

#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include "./parser_error.hpp"

namespace pstade { namespace biscuit {


template< int id, class Parser >
struct expect
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		typedef typename boost::range_result_iterator<State>::type iter_t;
		typedef typename boost::iterator_range<iter_t> range_t;

		if (!Parser::parse(s, us)) {
			throw parser_error<range_t, int>(
				boost::make_iterator_range(s.get_cur(), boost::end(s)), id
			);
		}

		return true;
	}
};


} } // namespace pstade::biscuit
