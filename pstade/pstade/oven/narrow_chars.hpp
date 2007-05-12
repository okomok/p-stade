#ifndef PSTADE_OVEN_NARROW_CHARS_HPP
#define PSTADE_OVEN_NARROW_CHARS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>


#define PSTADE_to_narrow(ch, loc) \
    std::use_facet< std::ctype<CharT> >(loc).narrow(ch) \
/**/

#define PSTADE_OVEN_DETAIL_XXX_CHARS_PARAMS (narrow_chars, PSTADE_to_narrow, char)
#include <pstade/oven/detail/xxx_chars.hpp>

#undef  PSTADE_to_narrow


#endif
