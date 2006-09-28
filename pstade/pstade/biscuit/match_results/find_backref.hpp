#ifndef PSTADE_BISCUIT_MATCH_RESULTS_FIND_BACKREF_HPP
#define PSTADE_BISCUIT_MATCH_RESULTS_FIND_BACKREF_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade_biscuit_extension {

    struct find_backref { };

}


namespace pstade { namespace biscuit {


template< class MatchResults, class ParsingSubRange > inline
bool pstade_biscuit_find_backref(MatchResults const& results, int id, ParsingSubRange& subrng)
{
    return pstade_biscuit_(pstade_biscuit_extension::find_backref(), results, id, subrng);
}


template< class MatchResults, class ParsingSubRange > inline
bool find_backref(MatchResults const& results, int id, ParsingSubRange& subrng)
{
    return pstade_biscuit_find_backref(results, id, subrng);
}


} } // namespace pstade::biscuit


#endif
