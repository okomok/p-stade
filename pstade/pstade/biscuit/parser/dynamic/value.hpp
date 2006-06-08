#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_VALUE_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_VALUE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../state/increment.hpp"
#include "../../state/is_end.hpp"


namespace pstade { namespace biscuit {


template< class ValueFtor >
struct value
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        if (biscuit::state_is_end(s))
            return false;

        if (ValueFtor()(us) != *s.get_cur())
            return false;

        biscuit::state_increment(s);
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
