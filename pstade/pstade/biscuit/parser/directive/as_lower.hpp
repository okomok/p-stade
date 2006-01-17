#pragma once

#if !defined(PSTADE_CFG_NO_STD_LOCALE)


#include <boost/iterator/iterator_traits.hpp> // for boost::iterator_value
#include <boost/range/result_iterator.hpp>
#include "../locale/converter/to_lower.hpp"
#include "./as_transformed.hpp"

namespace pstade { namespace biscuit {


template< class Parser >
struct as_lower
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		typedef typename boost::range_result_iterator<State>::type iter_t;

		return as_transformed<
			Parser,
			to_lower< typename boost::iterator_value<iter_t>::type >
		>::parse(s, us);
	}
};


} } // namespace pstade::biscuit


#endif // !defined(PSTADE_CFG_NO_STD_LOCALE)
