#ifndef PSTADE_BISCUIT_PARSER_LOCALE_BLANK_HPP
#define PSTADE_BISCUIT_PARSER_LOCALE_BLANK_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
