#ifndef PSTADE_BISCUIT_PARSER_UTILITY_BLANK_COM_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_BLANK_COM_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../config/nullary_parser.hpp"
#include "../primitive/chsetn.hpp"


namespace pstade { namespace biscuit {


PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(blank_com) :
	chset2<' ', '\t'>
{ };


} } // namespace pstade::biscuit


#endif
