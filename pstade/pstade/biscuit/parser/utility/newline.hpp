#ifndef PSTADE_BISCUIT_PARSER_UTILITY_NEWLINE_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_NEWLINE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../config/nullary_parser.hpp"
#include "../not_fwd.hpp"
#include "../orn.hpp"
#include "../primitive/char.hpp"
#include "../primitive/chseqn.hpp"
#include "../primitive/wchar.hpp"


namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(newline) :
    or_4<
        chseq2<0xD, 0xA>,   // CR+LF
        char_<0xA>,         // LF
        char_<0xD>,         // CR
        char_<0xC>          // FF
    >
{ };


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(wnewline) :
    or_4<
        PSTADE_BISCUIT_NULLARY_PARSER(newline),
        wchar<0x85>,        // NEL
        wchar<0x2028>,      // LS
        wchar<0x2029>       // PS
    >
{ };


// TODO: not eol
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(newline) >;


template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(wnewline) >;


} } // namespace pstade::biscuit


#endif
