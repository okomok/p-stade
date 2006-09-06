#ifndef PSTADE_BISCUIT_PARSER_DIRECTIVE_AS_FILTERED_HPP
#define PSTADE_BISCUIT_PARSER_DIRECTIVE_AS_FILTERED_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // distance
#include <boost/mpl/apply.hpp>
#include <pstade/oven/sub_range_base.hpp>
#include "../../range/filter_range.hpp"
#include "../../state/class_type.hpp"
#include "../../state/match_results_type.hpp"


namespace pstade { namespace biscuit {


template< class Parser, class FilterParser >
struct as_filtered
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename oven::sub_range_base<State>::type iter_rng_t;
        iter_rng_t rng(s.get_cur(), boost::end(s));

        typedef filter_range<FilterParser, iter_rng_t, UserState> fltr_rng_t;
        fltr_rng_t fltr_rng(rng, us);

        typedef typename state_class<State>::type state_class_t;
        typedef typename state_match_results<State>::type results_t;
        typedef typename boost::mpl::apply2<state_class_t, fltr_rng_t, results_t>::type
            fltr_state_t;

        fltr_state_t tmp(fltr_rng, s.results(), s.is_actionable());
        if (!Parser::parse(tmp, us))
            return false;

        s.set_cur( tmp.get_cur().base() );
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
