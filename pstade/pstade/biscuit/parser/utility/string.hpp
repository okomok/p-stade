#ifndef PSTADE_BISCUIT_PARSER_UTILITY_STRING_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_STRING_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/unused.hpp>
#include "../../config/nullary_parser.hpp"
#include "../../state/parse.hpp"


namespace pstade { namespace biscuit {


namespace string_detail {


    template< class State, class CharT >
    bool aux(State& s, CharT const *psz)
    {
        typename optional_iterator<State>::type
            opit = biscuit::state_parse(s, psz|oven::null_terminated);

        if (!opit)
            return false;

        s.set_cur(*opit);
        return true;
    }


} // namespace string_detail


#define PSTADE_BISCUIT_STRING(t, psz) \
    PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(t) \
    { \
        template< class State, class UserState > \
        static bool parse(State& s, UserState& us) \
        { \
            pstade::unused(us); \
            return string_detail::aux(s, psz); \
        } \
    }; \
/**/


} } // namespace pstade::biscuit


#endif
