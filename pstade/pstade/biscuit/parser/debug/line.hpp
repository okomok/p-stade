#pragma once

// Note: 'line' doesn't contain eol as std::getline doesn't.

#include "../../config/nullary_parser.hpp"
#include "../any.hpp"
#include "../star_before.hpp"
#include "./eol.hpp"

namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(line) :
	star_before<
		PSTADE_BISCUIT_NULLARY_PARSER(any),
		PSTADE_BISCUIT_NULLARY_PARSER(eol)
	>
{ };


} } // namespace pstade::biscuit
