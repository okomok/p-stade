#ifndef PSTADE_BISCUIT_STATE_PARSING_RANGE_STATE_TYPE_HPP
#define PSTADE_BISCUIT_STATE_PARSING_RANGE_STATE_TYPE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
