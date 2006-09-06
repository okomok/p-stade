#ifndef PSTADE_BISCUIT_PARSER_MAX_REPEAT_HPP
#define PSTADE_BISCUIT_PARSER_MAX_REPEAT_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unused.hpp>
#include "./repeat.hpp"


namespace pstade { namespace biscuit {


namespace max_repeat_detail {


    struct zero
    {
        template< class UserState >
        unsigned int operator()(UserState& us) const
        {
            pstade::unused(us);
            return 0;
        }
    };


} // namespace max_repeat_detail


template< class Parser, unsigned int max >
struct max_repeat :
    repeat<Parser, 0, max>
{ };


template< class Parser, class MaxFtor >
struct max_value_repeat :
    value_repeat<Parser, max_repeat_detail::zero, MaxFtor>
{ };


} } // namespace pstade::biscuit


#endif
