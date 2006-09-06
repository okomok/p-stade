#ifndef PSTADE_BISCUIT_PARSER_REPEAT_HPP
#define PSTADE_BISCUIT_PARSER_REPEAT_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/static_assert.hpp>
#include "../state/cur_guard.hpp"


namespace pstade { namespace biscuit {


namespace repeat_detail {


    template< class Parser, class State, class UserState >
    bool parse(State& s, UserState& us, unsigned int min, unsigned int max BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        state_cur_guard<State> gd(s);

        for (unsigned int i = 0; i < max; ++i) {
            if (!Parser::parse(s, us)) {
                if (i < min) // not enough
                    return false;
                else
                    break;
            }
        }

        gd.dismiss();
        return true;
    }


} // namespace repeat_detail


template< class Parser, unsigned int min, unsigned int max = min >
struct repeat
{
    BOOST_STATIC_ASSERT(0 <= min && min <= max);

    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        return repeat_detail::parse<Parser>(s, us, min, max);
    }
};


template< class Parser, class MinFtor, class MaxFtor = MinFtor >
struct value_repeat
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        unsigned int min = MinFtor(us);
        unsigned int max = MaxFtor(us);
        BOOST_ASSERT(0 <= min && min <= max);

        return repeat_detail::parse<Parser>(s, us, min, max);
    }
};


} } // namespace pstade::biscuit


#endif
