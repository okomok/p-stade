#ifndef PSTADE_BISCUIT_PARSER_UTILITY_DIGIT_COM_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_DIGIT_COM_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../config/nullary_parser.hpp"
#include "../primitive/chrng.hpp"


namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(digit_com) :
	chrng<'0', '9'>
{ };


} } // namespace pstade::biscuit


#endif
