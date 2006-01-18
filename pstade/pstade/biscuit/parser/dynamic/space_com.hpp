#pragma once

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
