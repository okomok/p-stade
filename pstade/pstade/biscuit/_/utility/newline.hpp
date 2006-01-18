#pragma once

#include "../../config/nullary_parser.hpp"
#include "../not_fwd.hpp"
#include "../orn.hpp"
#include "../primitive/char.hpp"
#include "../primitive/chseqn.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// newline
//
PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(newline) :
	or_3<
		chseq2<0xD, 0xA>,
		char_<0xA>,
		char_<0xD>
	>
{ };


///////////////////////////////////////////////////////////////////////////////
// TODO: not eol
//
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(newline) >;


} } // namespace pstade::biscuit
