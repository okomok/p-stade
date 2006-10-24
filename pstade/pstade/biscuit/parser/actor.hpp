#ifndef PSTADE_BISCUIT_PARSER_ACTOR_HPP
#define PSTADE_BISCUIT_PARSER_ACTOR_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/result_iterator.hpp>
#include <pstade/oven/iter_range.hpp>
#include "../action/null_action.hpp"
#include "../state/cur_guard.hpp"


namespace pstade { namespace biscuit {


template< class Parser, class Action >
struct actor
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        state_cur_guard<State> gd(s);

        if (!Parser::parse(s, us))
            return false;

        if (s.is_actionable()) {
            typedef typename boost::range_result_iterator<State>::type iter_t;
            oven::iter_range<iter_t> rng(gd.marker(), s.get_cur());

            Action()(rng, us);
        }

        gd.dismiss();
        return true;
    }
};


template< class Parser, class Action >
struct state_actor
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        state_cur_guard<State> gd(s);

        if (!Parser::parse(s, us))
            return false;

        if (s.is_actionable()) {
            typedef typename boost::range_result_iterator<State>::type iter_t;
            oven::iter_range<iter_t> rng(gd.marker(), s.get_cur());

            Action()(s, rng, us);
        }

        gd.dismiss();
        return true;
    }
};


// metafunctions
//

template< class Parser >
struct action_of
{
    typedef null_action type;
};

template< class Parser, class Action >
struct action_of< actor<Parser, Action> >
{
    typedef Action type;
};


template< class Parser >
struct remove_action
{
    typedef Parser type;
};

template< class Parser, class Action >
struct remove_action< actor<Parser, Action> > :
    remove_action<Parser>
{ };


} } // namespace pstade::biscuit


#endif
