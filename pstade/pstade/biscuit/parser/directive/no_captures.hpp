#ifndef PSTADE_BISCUIT_PARSER_DIRECTIVE_NO_CAPTURES_HPP
#define PSTADE_BISCUIT_PARSER_DIRECTIVE_NO_CAPTURES_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/range/end.hpp>
#include <pstade/oven/sub_range_base.hpp>
#include "../../match_results/null_match_results.hpp"
#include "../../match_results/parsing_range_type.hpp"
#include "../../state/class_type.hpp"
#include "../../state/match_results_type.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct no_captures
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename oven::sub_range_base<State>::type iter_rng_t;
        iter_rng_t rng(s.get_cur(), boost::end(s));
        
        typedef typename state_match_results<State>::type results_t;
        typedef typename match_results_parsing_range<results_t>::type parsing_range_t;
        typedef null_match_results<parsing_range_t> null_results_t;
        null_results_t null_results;

        typedef typename state_class<State>::type state_class_t;
        typedef typename boost::mpl::apply2<state_class_t, iter_rng_t, null_results_t>::type
            nocaps_state_t;

        nocaps_state_t tmp(rng, null_results, s.is_actionable());
        if (!Parser::parse(tmp, us))
            return false;

        s.set_cur(tmp.get_cur());
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
