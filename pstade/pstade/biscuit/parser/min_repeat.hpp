#ifndef PSTADE_BISCUIT_PARSER_MIN_REPEAT_HPP
#define PSTADE_BISCUIT_PARSER_MIN_REPEAT_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/static_assert.hpp>
#include "../state/cur_guard.hpp"


namespace pstade { namespace biscuit {


namespace min_repeat_detail {


    template< class Parser, class State, class UserState >
    bool parse(State& s, UserState& us, unsigned int min BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        state_cur_guard<State> gd(s);

        for (unsigned int i = 0; i < min; ++i) {
            if (!Parser::parse(s, us))
                return false;
        }

        gd.dismiss();
        return true;
    }


} // namespace min_repeat_detail


template< class Parser, unsigned int min >
struct min_repeat
{
    BOOST_STATIC_ASSERT(min >= 0);

    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        return min_repeat_detail::parse<Parser>(s, us, min);
    }
};


template< class Parser, class MinFtor >
struct min_value_repeat
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        unsigned int min = MinFtor(us);
        BOOST_ASSERT(min >= 0);

        return min_repeat_detail::parse<Parser>(s, us, min);
    }
};


} } // namespace pstade::biscuit


#endif
