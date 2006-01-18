#pragma once

#include "../../config/nullary_parser.hpp"
#include "../primitive/chrng.hpp"

namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(digit_com) :
	chrng<'0', '9'>
{ };


} } // namespace pstade::biscuit
