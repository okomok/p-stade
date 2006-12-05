#ifndef PSTADE_BISCUIT_ALGORITHM_MATCH_HPP
#define PSTADE_BISCUIT_ALGORITHM_MATCH_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/range/end.hpp>
#include <pstade/const.hpp>
#include <pstade/const_overloaded.hpp>
#include "../match_results/default_type.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"


namespace pstade { namespace biscuit {


namespace match_detail {


    template< class Parser, class ParsingRange, class MatchResults, class UserState > inline
    bool aux(ParsingRange& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;

        state_t s(r, rs);
        return Parser::parse(s, us) && (s.get_cur() == boost::end(r));
    }


} // namespace match_detail


template< class Parser, class ForwardRange, class UserState > inline
typename const_overloaded_result<bool, ForwardRange>::type
match(ForwardRange& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return match_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class UserState > inline
    bool match(ForwardRange const& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        typedef typename match_results_default<Parser, PSTADE_CONST(ForwardRange)>::type results_t;
        results_t rs;
        return match_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange > inline
typename const_overloaded_result<bool, ForwardRange>::type
match(ForwardRange& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return match_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange > inline
    bool match(ForwardRange const& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        typedef typename match_results_default<Parser, PSTADE_CONST(ForwardRange)>::type results_t;
        results_t rs;
        return match_detail::aux<Parser>(r, rs, null_state);
    }


template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
typename const_overloaded_result<bool, ForwardRange>::type
results_match(ForwardRange& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return match_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
    bool results_match(ForwardRange const& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        return match_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange, class MatchResults > inline
typename const_overloaded_result<bool, ForwardRange>::type
results_match(ForwardRange& r, MatchResults& rs BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return match_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange, class MatchResults > inline
    bool results_match(ForwardRange const& r, MatchResults& rs BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        return match_detail::aux<Parser>(r, rs, null_state);
    }


} } // namespace pstade::biscuit


#endif
