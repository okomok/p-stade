#ifndef PSTADE_BISCUIT_PARSER_UTILITY_ITERATION_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_ITERATION_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Thanks to:
//
// ITOU-T15


#include "../../action/null_action.hpp"
#include "../actor.hpp"
#include "../any.hpp"
#include "../directive/no_actions.hpp"
#include "../directive/no_captures.hpp"
#include "../orn.hpp"
#include "../star.hpp"
#include "../star_before.hpp"


namespace pstade { namespace biscuit {


template<
    class Parser,
    class RestAction = null_action
>
struct iteration :
    star<
        or_2<
            Parser,
            actor<
                star_before<
                    any,
                    no_captures< no_actions<Parser> > 
                >,
                RestAction
            >
        >
    >
{ };


} } // namespace pstade::biscuit


#endif
