#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_CONTROL_DO_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_CONTROL_DO_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


template< class BodyParser, class ConditionFtor >
struct do_
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        do {
            if (!BodyParser::parse(s, us))
                return false;
        } while (ConditionFtor()(us));

        return true;
    }
};


} } // namespace pstade::biscuit


#endif
