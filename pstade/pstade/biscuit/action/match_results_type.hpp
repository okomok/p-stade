#pragma once

namespace pstade { namespace biscuit {


template< class State >
struct state_match_results
{
	typedef typename State::match_results_type type;
};


} } // namespace pstade::biscuit
