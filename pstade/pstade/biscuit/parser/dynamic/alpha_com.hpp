#pragma once

#include "../../config/nullary_parser.hpp"
#include "../orn.hpp"
#include "../primitive/chrng.hpp"

namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(alpha_com) :
	or_2<
		chrng<'a', 'z'>,
		chrng<'A', 'Z'>
	>
{ };


} } // namespace pstade::biscuit
