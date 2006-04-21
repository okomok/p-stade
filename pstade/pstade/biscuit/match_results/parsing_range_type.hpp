#ifndef PSTADE_BISCUIT_MATCH_RESULTS_PARSING_RANGE_TYPE_HPP
#define PSTADE_BISCUIT_MATCH_RESULTS_PARSING_RANGE_TYPE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


template< class MatchResults >
struct match_results_parsing_range
{
    typedef typename MatchResults::pstade_biscuit_match_results_parsing_range_type type;
};


} } // namespace pstade::biscuit


#endif
