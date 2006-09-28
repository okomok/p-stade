#ifndef PSTADE_BISCUIT_MATCH_RESULTS_NULL_MATCH_RESULTS_HPP
#define PSTADE_BISCUIT_MATCH_RESULTS_NULL_MATCH_RESULTS_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <functional> // std::less
#include <map>
#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/sub_range.hpp>
#include <pstade/oven/sub_range_base.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace biscuit {


template< class ParsingRange >
struct null_match_results :
    std::map< int, typename oven::sub_range_base<ParsingRange>::type, std::less<int> > // always empty
{
    typedef ParsingRange pstade_biscuit_match_results_parsing_range_type;

    template< class ParsingSubRange > friend
    bool pstade_biscuit_find_backref(null_match_results<ParsingRange> const& self, int id, ParsingSubRange& subrng)
    {
        BOOST_ASSERT(boost::empty(self));
        pstade::unused(id, subrng);
        return false;
    }

    template< class ParsingSubRange > friend
    void pstade_biscuit_insert_backref(null_match_results<ParsingRange>& self, int id, ParsingSubRange& subrng)
    {
        BOOST_ASSERT(boost::empty(self));
        pstade::unused(id, subrng);
    }
};

/*
    template< class ParsingRange, class ParsingSubRange >
    bool pstade_biscuit_find_backref(null_match_results<ParsingRange> const& self, int id, ParsingSubRange& subrng)
    {
        BOOST_ASSERT(boost::empty(self));
        pstade::unused(id, subrng);
        return false;
    }

    template< class ParsingRange, class ParsingSubRange >
    void pstade_biscuit_insert_backref(null_match_results<ParsingRange>& self, int id, ParsingSubRange& subrng)
    {
        BOOST_ASSERT(boost::empty(self));
        pstade::unused(id, subrng);
    }
*/


} } // namespace pstade::biscuit


#endif
