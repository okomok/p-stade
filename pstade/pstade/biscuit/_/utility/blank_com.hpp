#pragma once

#include "../../config/nullary_parser.hpp"
#include "../primitive/chsetn.hpp"

namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(blank_com) :
	chset2<' ', '\t'>
{ };


} } // namespace pstade::biscuit
