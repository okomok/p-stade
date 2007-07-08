#ifndef PSTADE_BISCUIT_PARSER_DIRECTIVE_AS_TRANSFORMED_HPP
#define PSTADE_BISCUIT_PARSER_DIRECTIVE_AS_TRANSFORMED_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // distance
#include <boost/mpl/apply.hpp>
#include <pstade/oven/adapted_to_base.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/range_iterator.hpp>
#include <pstade/oven/transformed.hpp>
#include <pstade/result_of.hpp>
#include "../../state/class_type.hpp"
#include "../../state/match_results_type.hpp"


namespace pstade { namespace biscuit {


template<
    class Parser,
    class UnaryFun,
    class Reference = boost::use_default,
    class Value = boost::use_default
>
struct as_transformed
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename oven::iter_range_of<State>::type iter_rng_t;
        iter_rng_t rng(s.get_cur(), boost::end(s));

        typedef typename result_of<oven::xp_make_transformed<Reference, Value>(iter_rng_t&, UnaryFun)>::type
            trns_rng_t;

        trns_rng_t trns_rng = oven::xp_make_transformed<Reference, Value>()(rng, UnaryFun());

        typedef typename state_class<State>::type state_class_t;
        typedef typename state_match_results<State>::type results_t;
        typedef typename boost::mpl::apply2<state_class_t, trns_rng_t, results_t>::type
            trns_state_t;

        trns_state_t tmp(trns_rng, s.results(), s.is_actionable());
        if (!Parser::parse(tmp, us))
            return false;

        s.set_cur( oven::adapted_to<typename oven::range_iterator<State>::type>(tmp.get_cur()) );
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
