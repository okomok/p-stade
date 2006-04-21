#ifndef PSTADE_BISCUIT_PARSER_IDENTITY_HPP
#define PSTADE_BISCUIT_PARSER_IDENTITY_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


template< class Parser >
struct identity
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        return Parser::parse(s, us);
    }
};


} } // namespace pstade::biscuit


#endif
