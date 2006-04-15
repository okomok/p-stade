#ifndef PSTADE_BISCUIT_PARSER_UTILITY_LINE_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_LINE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
