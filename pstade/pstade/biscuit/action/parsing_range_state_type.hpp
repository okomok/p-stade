#pragma once

#include <boost/mpl/apply.hpp>
#include "./the_state_class.hpp"

namespace pstade { namespace biscuit {


template< class ParsingRange, class MatchResults >
struct parsing_range_state
{
	typedef typename boost::mpl::apply2<
		the_state_class,
		ParsingRange,
		MatchResults
	>::type type;
};


} } // namespace pstade::biscuit
