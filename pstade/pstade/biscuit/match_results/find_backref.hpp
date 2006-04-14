#ifndef PSTADE_BISCUIT_MATCH_RESULTS_FIND_BACKREF_HPP
#define PSTADE_BISCUIT_MATCH_RESULTS_FIND_BACKREF_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/overload.hpp>


namespace pstade { namespace biscuit {


template< class MatchResults, class ParsingSubRange > inline
bool find_backref(MatchResults& results, int id, ParsingSubRange& subrng)
{
	return pstade_biscuit_find_backref(results, id, subrng, overload());
}


} } // namespace pstade::biscuit


// default
//
template< class MatchResults, class ParsingSubRange > inline
bool pstade_biscuit_find_backref(MatchResults& results, int id, ParsingSubRange& subrng, ...)
{
	return results.pstade_biscuit_find_backref(id, subrng);
}


#endif
