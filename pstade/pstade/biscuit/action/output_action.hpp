#pragma once

#include <boost/foreach.hpp>
#include <boost/range/value_type.hpp>

namespace pstade { namespace biscuit {


struct output_action
{
	template< class ParsingSubRange, class UserState >
	void operator()(ParsingSubRange& rng, UserState& out) const
	{
		typedef typename boost::range_value<ParsingSubRange>::type value_t;
		BOOST_FOREACH (value_t const& val, rng) {
			out << val;
		}
	}
};


} } // namespace pstade::biscuit
