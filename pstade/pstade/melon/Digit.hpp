#ifndef PSTADE_MELON_DIGIT_HPP
#define PSTADE_MELON_DIGIT_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/bchrng.hpp>
#include <pstade/ustring.hpp> // ucs4_t


namespace pstade { namespace melon {


template<
    class = void
>
struct Digit :
    biscuit::or_<
        biscuit::bchrng<ucs4_t, 0x0030, 0x0039>,
        biscuit::bchrng<ucs4_t, 0x0660, 0x0669>

        // too many
        //

    >
{ };


} } // namespace pstade::melon


#endif
