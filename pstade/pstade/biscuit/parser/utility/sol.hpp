#ifndef PSTADE_BISCUIT_PARSER_UTILITY_SOL_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_SOL_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../config/nullary_parser.hpp"
#include "../after.hpp"
#include "../begin.hpp"
#include "../not_fwd.hpp"
#include "../orn.hpp"
#include "./newline.hpp"


namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(sol) :
    or_3<
        PSTADE_BISCUIT_NULLARY_PARSER(begin),
        after< PSTADE_BISCUIT_NULLARY_PARSER(newline), 1 >,
        after< PSTADE_BISCUIT_NULLARY_PARSER(newline), 2 >
    >
{ };


// TODO: not sol
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(sol) >;


} } // namespace pstade::biscuit


#endif
