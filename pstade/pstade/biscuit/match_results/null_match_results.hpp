#ifndef PSTADE_BISCUIT_MATCH_RESULTS_NULL_MATCH_RESULTS_HPP
#define PSTADE_BISCUIT_MATCH_RESULTS_NULL_MATCH_RESULTS_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/sub_range.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace biscuit {


template< class ParsingRange >
struct null_match_results
{
	typedef ParsingRange pstade_biscuit_match_results_parsing_range_type;

	template< class ParsingSubRange >
	bool pstade_biscuit_find_backref(int id, ParsingSubRange& subrng)
	{
		pstade::unused(id, subrng);
		return false;
	}

	template< class ParsingSubRange >
	void pstade_biscuit_insert_backref(int id, ParsingSubRange& subrng)
	{
		pstade::unused(id, subrng);
	}
};


} } // namespace pstade::biscuit


#endif
