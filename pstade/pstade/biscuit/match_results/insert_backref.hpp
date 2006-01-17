#pragma once

#include <pstade/overload.hpp>

namespace pstade { namespace biscuit {


//   Workaround:
//     subrng's type should have been 'ParsingSubRange const&', but 
//     VC6 cannot order two ctors of boost::iterator_range if the argument range is const-qualified.

template< class MatchResults, class ParsingSubRange > inline
void insert_backref(MatchResults& results, int id, ParsingSubRange& subrng)
{
	pstade_biscuit_insert_backref(results, id, subrng, overload());
}


} } // namespace pstade::biscuit


// default
template< class MatchResults, class ParsingSubRange > inline
void pstade_biscuit_insert_backref(MatchResults& results, int id, ParsingSubRange& subrng, ...)
{
	results.pstade_biscuit_insert_backref(id, subrng);
}
