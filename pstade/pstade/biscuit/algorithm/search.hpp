#ifndef PSTADE_BISCUIT_ALGORITHM_SEARCH_HPP
#define PSTADE_BISCUIT_ALGORITHM_SEARCH_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/end.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/range_iterator.hpp>
#include "../match_results/default_type.hpp"
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"


namespace pstade { namespace biscuit {


namespace search_detail {


    template< class Parser, class ParsingRange, class MatchResults, class UserState >
    typename oven::iter_range_of<ParsingRange>::type const
    aux(ParsingRange& r, MatchResults& rs, UserState& us)
    {
        typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;
        typedef typename oven::range_iterator<state_t>::type iter_t;

        state_t s(r, rs);
        for (; !biscuit::state_is_end(s); biscuit::state_increment(s)) {
            iter_t const marker = s.get_cur();
            if (Parser::parse(s, us))
                return oven::make_iter_range(marker, s.get_cur());
        }

        BOOST_ASSERT( boost::end(s) == boost::end(r) );
        return oven::make_iter_range(boost::end(s), boost::end(s));
    }


} // namespace search_detail


template< class Parser, class ForwardRange, class UserState > inline
typename oven::iter_range_of<ForwardRange>::type const
search(ForwardRange& r, UserState& us PSTADE_CONST_OVERLOADED(ForwardRange))
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return search_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class UserState > inline
    typename oven::iter_range_of<PSTADE_DEDUCED_CONST(ForwardRange)>::type const
    search(ForwardRange const& r, UserState& us)
    {
        typedef typename match_results_default<Parser, PSTADE_DEDUCED_CONST(ForwardRange)>::type results_t;
        results_t rs;
        return search_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange > inline
typename oven::iter_range_of<ForwardRange>::type const
search(ForwardRange& r PSTADE_CONST_OVERLOADED(ForwardRange))
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return search_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange > inline
    typename oven::iter_range_of<PSTADE_DEDUCED_CONST(ForwardRange)>::type const
    search(ForwardRange const& r)
    {
        typedef typename match_results_default<Parser, PSTADE_DEDUCED_CONST(ForwardRange)>::type results_t;
        results_t rs;
        return search_detail::aux<Parser>(r, rs, null_state);
    }


template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
typename oven::iter_range_of<ForwardRange>::type const
results_search(ForwardRange& r, MatchResults& rs, UserState& us PSTADE_CONST_OVERLOADED(ForwardRange))
{
    return search_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
    typename oven::iter_range_of<PSTADE_DEDUCED_CONST(ForwardRange)>::type const
    results_search(ForwardRange const& r, MatchResults& rs, UserState& us)
    {
        return search_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class MatchResults, class ForwardRange > inline
typename oven::iter_range_of<ForwardRange>::type const
results_search(ForwardRange& r, MatchResults& rs PSTADE_CONST_OVERLOADED(ForwardRange))
{
    return search_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class MatchResults, class ForwardRange > inline
    typename oven::iter_range_of<PSTADE_DEDUCED_CONST(ForwardRange)>::type const
    results_search(ForwardRange const& r, MatchResults& rs)
    {
        return search_detail::aux<Parser>(r, rs, null_state);
    }


} } // namespace pstade::biscuit


#endif
