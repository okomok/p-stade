#ifndef PSTADE_BISCUIT_PARSER_UTILITY_EOL_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_EOL_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../config/nullary_parser.hpp"
#include "../end.hpp"
#include "../not_fwd.hpp"
#include "../orn.hpp"
#include "./newline.hpp"


namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(eol) :
	or_2<
		PSTADE_BISCUIT_NULLARY_PARSER(newline),
		PSTADE_BISCUIT_NULLARY_PARSER(end)
	>
{ };


// TODO: not eol
//
template<>
struct not_< PSTADE_BISCUIT_NULLARY_PARSER(eol) >;


} } // namespace pstade::biscuit


#endif
