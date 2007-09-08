#ifndef PSTADE_BISCUIT_ALGORITHM_MATCH_HPP
#define PSTADE_BISCUIT_ALGORITHM_MATCH_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/make_function_of.hpp>
#include <pstade/egg/specified.hpp>
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"
#include "./detail/without_results.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct tp_results_match
{
    struct baby
    {
        template< class Myself, class ParsingRange, class MatchResults, class UserState = void >
        struct apply
        {
            typedef bool type;
        };

        template< class Result, class ParsingRange, class MatchResults, class UserState >
        Result call(ParsingRange& r, MatchResults& rs, UserState& us) const
        {
            typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;

            state_t s(r, rs);
            return Parser::parse(s, us) && (s.get_cur() == boost::end(r));
        }

        template< class Result, class ParsingRange, class MatchResults >
        Result call(ParsingRange& r, MatchResults& rs) const
        {
            return egg::make_function_of(*this)(r, rs, null_state);
        }
    };

    typedef egg::function<baby> type;
};


template< class Parser >
struct xp_results_match :
    tp_results_match<Parser>::type
{ };

#define  PSTADE_EGG_SPECIFIED_PARAMS ((2)(3), results_match, xp_results_match, 1)
#include PSTADE_EGG_SPECIFIED()


template< class Parser >
struct xp_match :
    detail::tp_without_results<xp_results_match, Parser>::type
{ };

#define  PSTADE_EGG_SPECIFIED_PARAMS ((1)(2), match, xp_match, 1)
#include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::biscuit


#endif
