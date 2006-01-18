#pragma once

#include "../../config/nullary_parser.hpp"
#include "./alpha_com.hpp"
#include "./digit_com.hpp"

namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(alnum_com) :
	or_2<
		PSTADE_BISCUIT_NULLARY_PARSER(alpha_com),
		PSTADE_BISCUIT_NULLARY_PARSER(digit_com)
	>
{ };


} } // namespace pstade::biscuit
