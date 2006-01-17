#pragma once

#include <pstade/overload.hpp>

namespace pstade { namespace biscuit {


template< class MatchResults, class ParsingSubRange > inline
bool find_backref(MatchResults& results, int id, ParsingSubRange& subrng)
{
	return pstade_biscuit_find_backref(results, id, subrng, overload());
}


} } // namespace pstade::biscuit


// default
template< class MatchResults, class ParsingSubRange > inline
bool pstade_biscuit_find_backref(MatchResults& results, int id, ParsingSubRange& subrng, ...)
{
	return results.pstade_biscuit_find_backref(id, subrng);
}
