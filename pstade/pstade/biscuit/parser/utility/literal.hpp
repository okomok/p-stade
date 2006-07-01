#ifndef PSTADE_BISCUIT_PARSER_UTILITY_LITERAL_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_LITERAL_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/algorithm.hpp> // find
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/unused.hpp>
#include "../../config/nullary_parser.hpp"
#include "../../state/increment.hpp"
#include "../../state/parse.hpp"


namespace pstade { namespace biscuit {


namespace literal_detail {


    template< class State, class Range >
    bool seq(State& s, Range& rng)
    {
        typename optional_iterator<State>::type
            opit = biscuit::state_parse(s, rng);

        if (!opit)
            return false;

        s.set_cur(*opit);
        return true;
    }


    template< class State, class Range >
    bool set(State& s, Range& rng)
    {
        if (biscuit::state_is_end(s))
            return false;

        if (boost::end(rng) == oven::find(rng, *s.get_cur()))
            return false;

        biscuit::state_increment(s);
        return true;
    }


} // namespace literal_detail


#define PSTADE_BISCUIT_SEQ_LITERAL(t, psz) \
    PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(t) \
    { \
        template< class State, class UserState > \
        static bool parse(State& s, UserState& us) \
        { \
            pstade::unused(us); \
            return literal_detail::seq(s, psz|oven::null_terminated); \
        } \
    }; \
/**/


#define PSTADE_BISCUIT_SET_LITERAL(t, psz) \
    PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(t) \
    { \
        template< class State, class UserState > \
        static bool parse(State& s, UserState& us) \
        { \
            pstade::unused(us); \
            return literal_detail::set(s, psz|oven::null_terminated); \
        } \
    }; \
/**/


} } // namespace pstade::biscuit


#endif
