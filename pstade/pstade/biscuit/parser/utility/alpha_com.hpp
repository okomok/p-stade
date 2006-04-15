#ifndef PSTADE_BISCUIT_PARSER_UTILITY_ALPHA_COM_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_ALPHA_COM_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
