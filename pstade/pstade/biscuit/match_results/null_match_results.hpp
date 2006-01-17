#pragma once

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
