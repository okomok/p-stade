#pragma once

#if !defined(PSTADE_CFG_NO_STD_LOCALE)


#include "../../config/nullary_parser.hpp"
#include "../orn.hpp"
#include "../primitive/char.hpp"
#include "./space.hpp"

namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(blank) :
	or_2< PSTADE_BISCUIT_NULLARY_PARSER(space), char_<'\t'> >
{ };


} } // namespace pstade::biscuit


#endif // !defined(PSTADE_CFG_NO_STD_LOCALE)
