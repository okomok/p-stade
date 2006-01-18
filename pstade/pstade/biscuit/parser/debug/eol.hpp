#pragma once

#include "../../config/nullary_parser.hpp"
#include "../end.hpp"
#include "../not_fwd.hpp"
#include "../orn.hpp"
#include "./newline.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// eol
//
PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(eol) :
	or_2<
		PSTADE_BISCUIT_NULLARY_PARSER(newline),
		PSTADE_BISCUIT_NULLARY_PARSER(end)
	>
{ };


///////////////////////////////////////////////////////////////////////////////
// TODO: not eol
//
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(eol) >;


} } // namespace pstade::biscuit
