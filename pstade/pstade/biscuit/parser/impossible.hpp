#ifndef PSTADE_BISCUIT_PARSER_IMPOSSIBLE_HPP
#define PSTADE_BISCUIT_PARSER_IMPOSSIBLE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "./not_fwd.hpp"


namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(impossible)
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        BOOST_ASSERT(false);

        pstade::unused(s, us);
        return false;
    }
};


template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(impossible) >;


} } // namespace pstade::biscuit


#endif
