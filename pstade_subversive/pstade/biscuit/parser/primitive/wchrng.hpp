#ifndef PSTADE_BISCUIT_PARSER_PRIMITIVE_WCHRNG_HPP
#define PSTADE_BISCUIT_PARSER_PRIMITIVE_WCHRNG_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./bchrng.hpp"


namespace pstade { namespace biscuit {


template< wchar_t min_ch, wchar_t max_ch >
struct wchrng :
    bchrng< wchar_t, min_ch, max_ch >
{ };


} } // namespace pstade::biscuit


#endif
