#ifndef PSTADE_BISCUIT_PARSER_PRIMITIVE_WCHAR_HPP
#define PSTADE_BISCUIT_PARSER_PRIMITIVE_WCHAR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./bchar.hpp"


namespace pstade { namespace biscuit {


template< wchar_t ch >
struct wchar :
	bchar< wchar_t, ch >
{ };


} } // namespace pstade::biscuit


#endif
