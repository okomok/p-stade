#ifndef PSTADE_BISCUIT_ALGORITHM_MATCH_HPP
#define PSTADE_BISCUIT_ALGORITHM_MATCH_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include "../match_results/default_type.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"


namespace pstade { namespace biscuit {


namespace match_detail {


    template< class Parser, class ParsingRange, class MatchResults, class UserState > inline
    bool aux(ParsingRange& r, MatchResults& rs, UserState& us)
    {
        typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;

        state_t s(r, rs);
        return Parser::parse(s, us) && (s.get_cur() == boost::end(r));
    }


} // namespace match_detail


template< class Parser, class ForwardRange, class UserState > inline
bool match(ForwardRange& r, UserState& us, typename const_overloaded<ForwardRange>::type = 0)
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return match_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class UserState > inline
    bool match(ForwardRange const& r, UserState& us)
    {
        typedef typename match_results_default<Parser, typename boost::add_const<ForwardRange>::type>::type results_t;
        results_t rs;
        return match_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange > inline
bool match(ForwardRange& r, typename const_overloaded<ForwardRange>::type = 0)
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return match_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange > inline
    bool match(ForwardRange const& r)
    {
        typedef typename match_results_default<Parser, typename boost::add_const<ForwardRange>::type>::type results_t;
        results_t rs;
        return match_detail::aux<Parser>(r, rs, null_state);
    }


template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
bool results_match(ForwardRange& r, MatchResults& rs, UserState& us, typename const_overloaded<ForwardRange>::type = 0)
{
    return match_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
    bool results_match(ForwardRange const& r, MatchResults& rs, UserState& us)
    {
        return match_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange, class MatchResults > inline
bool results_match(ForwardRange& r, MatchResults& rs, typename const_overloaded<ForwardRange>::type = 0)
{
    return match_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange, class MatchResults > inline
    bool results_match(ForwardRange const& r, MatchResults& rs)
    {
        return match_detail::aux<Parser>(r, rs, null_state);
    }


} } // namespace pstade::biscuit


#endif
