#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_SEQ_RANGE_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_SEQ_RANGE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../state/parse.hpp"
#include "./identity_fun.hpp"


namespace pstade { namespace biscuit {


template< class RangeFtor = identity_fun >
struct seq_range
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typename optional_iterator<State>::type
            opit = biscuit::state_parse(s, RangeFtor()(us));

        if (!opit)
            return false;

        s.set_cur(*opit);
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
