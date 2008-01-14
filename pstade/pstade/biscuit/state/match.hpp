#ifndef PSTADE_BISCUIT_STATE_MATCH_HPP
#define PSTADE_BISCUIT_STATE_MATCH_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include "./is_end.hpp"


namespace pstade { namespace biscuit {


template< class Parser, class ForwardRange, class State, class UserState >
bool state_match(ForwardRange& r, State& s, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    State tmp(r, s.results(), s.is_actionable());
    Parser::parse(tmp, us);
    return biscuit::state_is_end(tmp);
}


} } // namespace pstade::biscuit


#endif
