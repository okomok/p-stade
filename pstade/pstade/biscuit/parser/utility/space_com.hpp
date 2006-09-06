#ifndef PSTADE_BISCUIT_PARSER_UTILITY_SPACE_COM_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_SPACE_COM_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../config/nullary_parser.hpp"
#include "../orn.hpp"
#include "./blank_com.hpp"
#include "./newline.hpp"


namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(space_com) :
    or_2<
        PSTADE_BISCUIT_NULLARY_PARSER(blank_com),
        PSTADE_BISCUIT_NULLARY_PARSER(newline)
    >
{ };


} } // namespace pstade::biscuit


#endif
