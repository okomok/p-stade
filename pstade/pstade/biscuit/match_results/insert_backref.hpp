#ifndef PSTADE_BISCUIT_MATCH_RESULTS_INSERT_BACKREF_HPP
#define PSTADE_BISCUIT_MATCH_RESULTS_INSERT_BACKREF_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade_biscuit_extension {

    struct insert_backref { };

}


namespace pstade { namespace biscuit {


template< class MatchResults, class ParsingSubRange > inline
void pstade_biscuit_insert_backref(MatchResults& results, int id, ParsingSubRange& subrng)
{
    pstade_biscuit_(pstade_biscuit_extension::insert_backref(), results, id, subrng);
}


template< class MatchResults, class ParsingSubRange > inline
void insert_backref(MatchResults& results, int id, ParsingSubRange& subrng)
{
    pstade_biscuit_insert_backref(results, id, subrng);
}


} } // namespace pstade::biscuit


#endif
