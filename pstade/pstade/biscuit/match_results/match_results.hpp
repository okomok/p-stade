#ifndef PSTADE_BISCUIT_MATCH_RESULTS_MATCH_RESULTS_HPP
#define PSTADE_BISCUIT_MATCH_RESULTS_MATCH_RESULTS_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <functional> // std::less
#include <map>
#include <utility> // std::pair
#include <boost/range/end.hpp>
#include <pstade/oven/range_iterator.hpp>
#include <pstade/oven/sub_range_base.hpp>


namespace pstade { namespace biscuit {


template< class ParsingRange >
struct match_results :
    std::map< int, typename oven::sub_range_base<ParsingRange>::type, std::less<int> >
{
private:
    typedef typename oven::sub_range_base<ParsingRange>::type stored_range_t;
    typedef std::map< int, stored_range_t, std::less<int> > super_t;

public:
    typedef ParsingRange pstade_biscuit_match_results_parsing_range_type;
};


template< class ParsingRange, class ParsingSubRange >
bool pstade_biscuit_find_backref(match_results<ParsingRange> const& self, int id, ParsingSubRange& subrng)
{
    typedef typename oven::
        range_iterator<match_results<ParsingRange> const>::type iter_t;

    iter_t const it = self.find(id);
    if (it != boost::end(self)) {
        subrng = it->second;
        return true;
    }

    return false;
}


template< class ParsingRange, class ParsingSubRange >
void pstade_biscuit_insert_backref(match_results<ParsingRange>& self, int id, ParsingSubRange& subrng)
{
    typedef typename oven::
        range_iterator<match_results<ParsingRange> >::type iter_t;

    std::pair<iter_t, bool> ret = self.insert(std::make_pair(id, subrng));
    if (!ret.second) // overwrite
        ret.first->second = subrng;
}


} } // namespace pstade::biscuit


#endif
