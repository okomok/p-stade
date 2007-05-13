#ifndef PSTADE_BISCUIT_ALGORITHM_ITERATE_HPP
#define PSTADE_BISCUIT_ALGORITHM_ITERATE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Deprecated. Prefer the 'iteration' parser.


#include <boost/foreach.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/range_iterator.hpp>
#include <pstade/oven/sub_range.hpp>
#include <pstade/unused.hpp>
#include "../parser/directive/no_actions.hpp"
#include "../parser/directive/no_captures.hpp"
#include "../range/token_range.hpp"
#include "../state/null_state.hpp"
#include "./parse.hpp"


namespace pstade { namespace biscuit {


namespace iterate_detail {


    template< class ForwardIter, class UserState, class GapAction >
    void aux_action(ForwardIter first, ForwardIter last, UserState& us, GapAction action)
    {
        if (first != last) {
            oven::iter_range<ForwardIter> rng(first, last);
            action(rng, us);
        }
    }


    template< class Parser, class ParsingRange, class UserState, class GapAction >
    void aux(ParsingRange& r, UserState& us, GapAction action)
    {
        typedef typename oven::range_iterator<ParsingRange>::type iter_t;
        iter_t last = boost::end(r);
        iter_t last_parsed = boost::begin(r);

        token_range< no_captures< no_actions<Parser> >, ParsingRange, UserState > trng(r, us);
        BOOST_FOREACH (oven::sub_range<ParsingRange> sr, trng) {
            iterate_detail::aux_action(last_parsed, boost::begin(sr), us, action);

            // Note:
            // You cannot use 'match<Parser>(sr, us)'.
            // For instance, think about parser 'before<eol>'.
            // Note:
            // The comment above is impossible to understand.
            // Never write the question as comment.
            biscuit::parse<Parser>(oven::make_iter_range(boost::begin(sr), last), us);

            last_parsed = boost::end(sr);
        }

        iterate_detail::aux_action(last_parsed, last, us, action);
    }


} // namespace iterate_detail


template< class Parser, class ForwardRange, class UserState, class GapAction > inline
void iterate(ForwardRange& r, UserState& us, GapAction action PSTADE_CONST_OVERLOADED(ForwardRange))
{
    iterate_detail::aux<Parser>(r, us, action);
}

    template< class Parser, class ForwardRange, class UserState, class GapAction > inline
    void iterate(ForwardRange const& r, UserState& us, GapAction action)
    {
        iterate_detail::aux<Parser>(r, us, action);
    }


// no user-state
template< class Parser, class ForwardRange, class UserState, class GapAction > inline
void iterate(ForwardRange& r, GapAction action PSTADE_CONST_OVERLOADED(ForwardRange))
{
    iterate_detail::aux<Parser>(r, null_state, action);
}

    template< class Parser, class ForwardRange, class UserState, class GapAction > inline
    void iterate(ForwardRange const& r, GapAction action)
    {
        iterate_detail::aux<Parser>(r, null_state, action);
    }


// iterate without gap-actions
//
namespace iterate_detail {


    template< class Parser, class ForwardRange, class UserState >
    void aux_without_gap_actions(ForwardRange& r, UserState& us)
    {
        token_range<Parser, ForwardRange, UserState> trng(r, us);
        BOOST_FOREACH (boost::sub_range<ForwardRange> sr, trng) {
            pstade::unused(sr);
        }
    }


} // namespace iterate_detail


template< class Parser, class ForwardRange, class UserState > inline
void iterate(ForwardRange& r, UserState& us PSTADE_CONST_OVERLOADED(ForwardRange))
{
    iterate_detail::aux_without_gap_actions<Parser>(r, us);
}

    template< class Parser, class ForwardRange, class UserState > inline
    void iterate(ForwardRange const& r, UserState& us)
    {
        iterate_detail::aux_without_gap_actions<Parser>(r, us);
    }


// no user-state
template< class Parser, class ForwardRange > inline
void iterate(ForwardRange& r PSTADE_CONST_OVERLOADED(ForwardRange))
{
    iterate_detail::aux_without_gap_actions<Parser>(r, null_state);
}

    template< class Parser, class ForwardRange > inline
    void iterate(ForwardRange const& r)
    {
        iterate_detail::aux_without_gap_actions<Parser>(r, null_state);
    }


} } // namespace pstade::biscuit


#endif
