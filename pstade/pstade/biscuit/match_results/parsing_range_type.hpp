#pragma once

namespace pstade { namespace biscuit {


template< class MatchResults >
struct match_results_parsing_range
{
	typedef typename MatchResults::pstade_biscuit_match_results_parsing_range_type type;
};


} } // namespace pstade::biscuit
