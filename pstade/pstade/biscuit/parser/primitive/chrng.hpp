#ifndef PSTADE_BISCUIT_PARSER_PRIMITIVE_CHRNG_HPP
#define PSTADE_BISCUIT_PARSER_PRIMITIVE_CHRNG_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./bchrng.hpp"


namespace pstade { namespace biscuit {


template< char min_ch, char max_ch >
struct chrng :
	bchrng< char, min_ch, max_ch >
{ };


} } // namespace pstade::biscuit


#endif
